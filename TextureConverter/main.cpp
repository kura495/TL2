#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <d3d12.h>

#include "TextureConverter/TextureConverter.h"

enum Argument {
	kApplicationPath,	//アプリケーションのパス
	kFilePath,			//消されたファイルのパス

	NumArgument
};

int main(int argc, char* argv[]) {
	
	assert(argc >= NumArgument);
	
	//COMライブラリの初期化
	HRESULT hr = CoInitializeEx(nullptr,COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	//テクスチャコンバータ
	TextureConverter converter;

	converter.ConvertTextureWICToDDS(argv[kFilePath]);

	//COMライブラリの終了
	CoUninitialize();

	return 0;
}