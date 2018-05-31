#include "stdafx.h"
#include "SpriteFontLoader.h"
#include "../Helpers/BinaryReader.h"
#include "../Content/ContentManager.h"
#include "../Graphics/TextRenderer.h"
#include "../Graphics/TextureData.h"


SpriteFontLoader::SpriteFontLoader()
{

}


SpriteFontLoader::~SpriteFontLoader()
{
}

#pragma warning( disable : 4702 )
SpriteFont* SpriteFontLoader::LoadContent(const wstring& assetFile)
{
	auto pBinReader = new BinaryReader(); //Prevent memory leaks
	pBinReader->Open(assetFile);

	if (!pBinReader->Exists())
	{
		delete pBinReader;
		Logger::LogFormat(LogLevel::Error, L"SpriteFontLoader::LoadContent > Failed to read the assetFile!\nPath: \'%s\'", assetFile.c_str());
		
		return nullptr;
	}

	//See BMFont Documentation for Binary Layout
	
	//Parse the Identification bytes (B,M,F)
	int b = pBinReader->Read<char>();
	int m = pBinReader->Read<char>();
	int f = pBinReader->Read<char>();

	//wstring message{ to_wstring(b) + to_wstring(m) + to_wstring(f) };
	//Logger::LogInfo(message);

	//If Identification bytes doesn't match B|M|F,
	if (b != 'B' && m != 'M' && f != 'F')
	{
		Logger::LogError(L"Incorrect SpriteFontLoader::LoadContent > Not a valid .fnt font");
		delete pBinReader;
		return nullptr;
	}
	//Log Error (SpriteFontLoader::LoadContent > Not a valid .fnt font) &
	//return nullptr
	//...

	//Parse the version (version 3 required)
	int versionNum = pBinReader->Read<char>();
	//If version is < 3,
	if (versionNum != 3)
	{
		Logger::LogError(L"SpriteFontLoader::LoadContent > Only .fnt version 3 is supported");
		delete pBinReader;
		return nullptr;
	}
	//Log Error (SpriteFontLoader::LoadContent > Only .fnt version 3 is supported)
	//return nullptr
	//...

	//Valid .fnt file
	auto pSpriteFont = new SpriteFont();
	//SpriteFontLoader is a friend class of SpriteFont
	//That means you have access to its privates (pSpriteFont->m_FontName = ... is valid)
	//pSpriteFont->m_FontName = 

	//**********
	// BLOCK 0 *
	//**********
	//Retrieve the blockId and blockSize
	int blockId = pBinReader->Read<char>();
	int blockSize = pBinReader->Read<int>();

	//Retrieve the FontSize (will be -25, BMF bug) [SpriteFont::m_FontSize]
	pSpriteFont->m_FontSize = static_cast<short>(pBinReader->Read<int>());

	//Move the binreader to the start of the FontName [BinaryReader::MoveBufferPosition(...) 
	//or you can set its position using BinaryReader::SetBufferPosition(...))
	//Retrieve the FontName [SpriteFont::m_FontName]
	//...
	pBinReader->MoveBufferPosition(12);
	pSpriteFont->m_FontName = pBinReader->Read<wstring>();


	//**********
	// BLOCK 1 *
	//**********
	//Retrieve the blockId and blockSize
	blockId = pBinReader->Read<char>();
	blockSize = pBinReader->Read<int>();

	//Retrieve Texture Width & Height [SpriteFont::m_TextureWidth/m_TextureHeight]
	pBinReader->MoveBufferPosition(4);

	pSpriteFont->m_TextureWidth = pBinReader->Read<UINT>();
	pSpriteFont->m_TextureHeight = pBinReader->Read<UINT>();
	
	//Retrieve PageCount
	//> if pagecount > 1
	//> Log Error (SpriteFontLoader::LoadContent > SpriteFont (.fnt): Only one texture per font allowed)
	//Advance to Block2 (Move Reader)
	//...
	UINT pages = pBinReader->Read<UINT>();

	if (pages > 1)
	{
		Logger::LogError(L"SpriteFontLoader::LoadContent > SpriteFont (.fnt): Only one texture per font allowed");
		delete pBinReader;
		return nullptr;
	}

	pBinReader->MoveBufferPosition(6);

	//**********
	// BLOCK 2 *
	//**********
	//Retrieve the blockId and blockSize
	blockId = pBinReader->Read<char>();
	blockSize = pBinReader->Read<int>();

	wstring pageName = pBinReader->Read<wstring>();

	//Retrieve the PageName (store Local)
	//	> If PageName is empty
	//	> Log Error (SpriteFontLoader::LoadContent > SpriteFont (.fnt): Invalid Font Sprite [Empty])
	//>Retrieve texture filepath from the assetFile path
	//> (ex. c:/Example/somefont.fnt => c:/Example/) [Have a look at: wstring::rfind()]
	//>Use path and PageName to load the texture using the ContentManager [SpriteFont::m_pTexture]
	//> (ex. c:/Example/ + 'PageName' => c:/Example/somefont_0.png)
	//...
	
	if (pageName.empty())
	{
		Logger::LogError(L"SpriteFontLoader::LoadContent > SpriteFont (.fnt): Invalid Font Sprite [Empty]");
		delete pBinReader;
		return nullptr;
	}

	wstring key(L"/");
	size_t found = assetFile.rfind(key);

	const wstring path (assetFile.substr(0,found) + pageName);

	pSpriteFont->m_pTexture = ContentManager::Load<TextureData>(path);

	//**********
	// BLOCK 3 *
	//**********
	//Retrieve the blockId and blockSize
	blockId = pBinReader->Read<char>();
	blockSize = pBinReader->Read<int>();

	//Retrieve Character Count (see documentation)
	int charCount = blockSize / 20;

	//Retrieve Every Character, For every Character:
	for (int i = 0; i < charCount;  i++ )
	{
		wchar_t CharacterId = static_cast<wchar_t>(pBinReader->Read<UINT>());

		if (!pSpriteFont->IsCharValid(CharacterId))
		{
			Logger::LogWarning(L"SpriteFontLoader::LoadContent > SpriteFont (.fnt): Invalid Font Sprite [Empty]");
			pBinReader->MoveBufferPosition(blockSize);
			break;
		}
		
		FontMetric metric = pSpriteFont->GetMetric(CharacterId);

		metric.IsValid = true;

		metric.Character = CharacterId;

		UINT x = pBinReader->Read<UINT>();
		UINT y = pBinReader->Read<UINT>();

		metric.Width = pBinReader->Read<UINT>();
		metric.Height = pBinReader->Read<UINT>();
		metric.OffsetX = pBinReader->Read<int>();
		metric.OffsetY = pBinReader->Read<int>();
		metric.AdvanceX = pBinReader->Read<int>();
		metric.Page = pBinReader->Read<UINT>();
		metric.Channel = pBinReader->Read<UINT>();

		metric.TexCoord.x = 0.0f;
		metric.TexCoord.y = 0.0f;
	}
	//> Retrieve CharacterId (store Local) and cast to a 'wchar_t'
	//> Check if CharacterId is valid (SpriteFont::IsCharValid), Log Warning and advance to next character if not valid
	//> Retrieve the corresponding FontMetric (SpriteFont::GetMetric) [REFERENCE!!!]
	//> Set IsValid to true [FontMetric::IsValid]
	//> Set Character (CharacterId) [FontMetric::Character]
	//> Retrieve Xposition (store Local)
	//> Retrieve Yposition (store Local)
	//> Retrieve & Set Width [FontMetric::Width]
	//> Retrieve & Set Height [FontMetric::Height]
	//> Retrieve & Set OffsetX [FontMetric::OffsetX]
	//> Retrieve & Set OffsetY [FontMetric::OffsetY]
	//> Retrieve & Set AdvanceX [FontMetric::AdvanceX]
	//> Retrieve & Set Page [FontMetric::Page]
	//> Retrieve Channel (BITFIELD!!!) 
	//	> See documentation for BitField meaning [FontMetrix::Channel]
	//> Calculate Texture Coordinates using Xposition, Yposition, TextureWidth & TextureHeight [FontMetric::TexCoord]
	//...
	
	
	//DONE :)

	delete pBinReader;
	return pSpriteFont;
	
	#pragma warning(default:4702)  
}

void SpriteFontLoader::Destroy(SpriteFont* objToDestroy)
{
	SafeDelete(objToDestroy);
}