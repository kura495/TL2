#pragma once
#include <string>

//テクスチャコンバーター
class TextureConverter
{
public:
	/// <summary>
	/// テクスチャをWICからDDSに変換する
	/// </summary>
	void ConvertTextureWICToDDS(const std::string& filePath);

private:
	/// <summary>
	/// マルチバイト文字列をワイド文字列に変換
	/// </summary>
	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);

};