
struct ConstantBuffer {
	XMMATRIX mWorld;		//ワールド変換行列
	XMMATRIX mView;			//ビュー変換行列
	XMMATRIX mProjection;	//透視射影変換行列
};

int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpCmdLine,
					 int nCmdShow) {
#ifdef _Debug
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	GFW::WindowDevice &window = GFW::WindowDevice::getInstance();

	GFW::DX11Device &device = GFW::DX11Device::getInstance();

	GFW::Math::Vertex vex[] = {
		{ 0.3f,0.5f,1.0f,0.0f,1,0, 0,1,1,1},
		{-0.3f,0.5f,1.0f,0.0f,0,0, 1,0,1,1},
		{ 0.3f,-0.5f,1.0f,0.0f,1,1, 1,1,0,1},
		{-0.3f,-0.5f,1.0f,0.0f,0,1, 1,1,1,1},
	};

	//DirectX11デバイスも同時に初期化がかかる
	window.Init(hInstance, nCmdShow, TEXT("GFW"), 1280, 720, true);

	COMPTR(ID3D11Buffer) vexbuffer;
	ID3D11Buffer *buf = nullptr;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(vex);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	device.getDevice()->CreateBuffer(&bd, nullptr, &buf);

	D3D11_MAPPED_SUBRESOURCE ms;
	device.getContext()->Map(buf, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, vex, sizeof(vex));
	device.getContext()->Unmap(buf, NULL);

	vexbuffer.Attach(buf);
	COMPTR(ID3D11VertexShader) vsmain;
	COMPTR(ID3D11PixelShader) psmain;
	ID3D11VertexShader *vsmain_buf;
	ID3D11PixelShader *psmain_buf;

	ID3D10Blob *vsbuf, *psbuf;
	D3DX11CompileFromFile(TEXT("./Shader/VS_Main2.hlsl"), 0, 0, "main", "vs_5_0", 0, 0, 0, &vsbuf, 0, 0);
	D3DX11CompileFromFile(TEXT("./Shader/PS_Main4.hlsl"), 0, 0, "main", "ps_5_0", 0, 0, 0, &psbuf, 0, 0);
	device.getDevice()->CreateVertexShader(vsbuf->GetBufferPointer(), vsbuf->GetBufferSize(), nullptr, &vsmain_buf);
	device.getDevice()->CreatePixelShader(psbuf->GetBufferPointer(), psbuf->GetBufferSize(), nullptr, &psmain_buf);

	vsmain.Attach(vsmain_buf);
	psmain.Attach(psmain_buf);


	ConstantBuffer mtx;

	XMVECTOR hEye = XMVectorSet(0.0f, 0.0f, -2.0f, 0.0f);	//カメラの位置
	XMVECTOR hAt = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);		//焦点の位置
	XMVECTOR hUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	mtx.mView = XMMatrixLookAtLH(hEye, hAt, hUp);
	mtx.mWorld = XMMatrixIdentity();
	mtx.mProjection = XMMatrixOrthographicLH(1280, 720, 1, 5000);


	//テクスチャの読み込み
	GFW::Texture2D tex;
	tex.LoadFile(TEXT("./resrc/lenna.jpg"));
	tex.getTex();

	ID3D11ShaderResourceView *srv[] = {
		tex.getSRV()
	};
	device.getContext()->PSSetShaderResources(0, sizeof(srv) / sizeof(srv[0]), srv);

	COMPTR(ID3D11Buffer) constantbuffer;
	buf = nullptr;

	//constantバッファ生成
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = sizeof(float);
	if (FAILED(device.getDevice()->CreateBuffer(&bd, NULL, &constantbuffer))) {
	}


	ConstantBuffer hConstantBuffer;
	hConstantBuffer.mWorld = XMMatrixTranspose(mtx.mWorld);
	hConstantBuffer.mView = XMMatrixTranspose(mtx.mView);
	hConstantBuffer.mProjection = XMMatrixTranspose(mtx.mProjection);


	device.getContext()->UpdateSubresource(constantbuffer, 0, NULL, &mtx, 0, 0);

	//コンテキストに設定
	device.getContext()->VSSetConstantBuffers(0, 1, &constantbuffer);






	//InputLayoutを作る前にシェーダーの生成を行う必要がある
	D3D11_INPUT_ELEMENT_DESC element[] ={
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	COMPTR(ID3D11InputLayout) layout;
	ID3D11InputLayout * inputlayout;

	device.getDevice()->CreateInputLayout(element, ARRAYSIZE(element),
										  vsbuf->GetBufferPointer(), vsbuf->GetBufferSize(), &inputlayout);

	layout.Attach(inputlayout);


	COMPTR(ID3D11RasterizerState) rasterizer;
	ID3D11RasterizerState* rasterizerState = NULL;
	D3D11_RASTERIZER_DESC rasterizerDesc =
	{
		D3D11_FILL_SOLID, // ワイヤーフレーム
		D3D11_CULL_FRONT,      // 裏面ポリゴンをカリングします
		FALSE,
		0,
		0.0f,
		FALSE,
		FALSE,
		FALSE,
		FALSE,
		FALSE
	};
	device.getDevice()->CreateRasterizerState(&rasterizerDesc, &rasterizerState);
	rasterizer.Attach(rasterizerState);

	// ラスタライザーステート設定
	device.getContext()->RSSetState(rasterizer.GetInterfacePtr());

	//頂点の並び方の設定
	device.getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//パイプラインにバッファーのセット
	UINT stride = sizeof(GFW::Math::Vertex);
	UINT offset = 0;
	device.getContext()->IASetVertexBuffers(0, 1, &vexbuffer.GetInterfacePtr(), &stride, &offset);


	//パイプライン回りの設定
	device.getContext()->IASetInputLayout(layout.GetInterfacePtr());
	device.getContext()->VSSetShader(vsmain.GetInterfacePtr(), 0, 0);
	device.getContext()->PSSetShader(psmain.GetInterfacePtr(), 0, 0);

	DEBUG(GFW::GUI::Default::Init_Commands());
	DEBUG(GFW::GUI::Default::Init_Quickstart());


	auto function = []() {
		DEBUG(static bool show_test_window = true);
		GFW::Shader &sh = GFW::Shader::getInstance();
		GFW::DX11Device &device = GFW::DX11Device::getInstance();
		float clear[4] = { 0.3f,0.3f,0.3f,1.0f };
		device.getContext()->ClearRenderTargetView(device.getRTV(), clear);
		device.getContext()->ClearDepthStencilView(device.getDSV(), D3D10_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		ID3D11RenderTargetView *rtv[] = {
			device.getRTV(),
		};
		//device.getContext()->OMSetRenderTargets(1, rtv, device.getDSV());

		DEBUG(ImGui_ImplDX11_NewFrame());
		//Drawコールの呼び出し(描画コマンドの発行)
		device.getContext()->Draw(4, 0);

		//Gui描画
		GFW::Gui::getInstance().Draw();

		DEBUG(if (show_test_window) {
			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
			ImGui::ShowTestWindow(&show_test_window);
		});

		static GFW::Type::GFW_RASTERIZER_DESC rs;
		GFW::GUI::Selector_RASTERIZER_DESC(rs);
		static GFW::Type::GFW_INPUT_ELEMENT_DESC_ARRAY elem;
		GFW::GUI::Selector_INPUT_ELEMENT_DESC_ARRAY(elem);

		device.getContext()->OMSetRenderTargets(1,rtv, nullptr);

		DEBUG(device.getAnotation()->BeginEvent(L"ImGui"));
		DEBUG(ImGui::Render());
		DEBUG(device.getAnotation()->EndEvent());

		device.getSwapChain()->Present(0, 0);
	};
	window.MessageLoop(function);


	return 0;
}

