#include "MapParser.h"
#include "UtilDebug.h"
MapParser *MapParser::s_Instance = nullptr;

bool MapParser::Load(){
    return Parse("MAP", "assets/maps/map.tmx");
}

bool MapParser::Parse(std::string id, std::string source){
    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error())
    {
        std::cerr << "Failed to load: " << source << std::endl;
        return false;
    }

    TiXmlElement *root = xml.RootElement();
    int rowcount=0, colcount=0, tilesize=0;
    root->Attribute("width", &colcount);
    root->Attribute("height", &rowcount);
    root->Attribute("tilewidth", &tilesize);

    //Parse tile sets
    TilesetList tilesets;
    for(TiXmlElement *e=root->FirstChildElement(); e!=nullptr; e=e->NextSiblingElement())
    {
        if(e->Value() == std::string("tileset"))
        {
            tilesets.push_back(ParseTileset(e));
        }
    }

    //Parse Layers
    GameMap *gamemap = new GameMap();

    for(TiXmlElement *e=root->FirstChildElement(); e!=nullptr; e=e->NextSiblingElement())
    {
        if(e->Value() == std::string("layer"))
        {
            #if IS_LOAD_PRINTABLE == 1
                std::cout << ">>ParseTileLayer:"<< rowcount<<std::endl;
            #endif
            TileLayer *tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
            gamemap->m_MapLayers.push_back(tilelayer);
        }
    }
    m_MapDict[id] = gamemap;
    return true;
}

Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset){
    Tileset tileset;
    tileset.Name = xmlTileset->Attribute("name");
    #if IS_LOAD_PRINTABLE == 1
        std::cout << "tilesetname:"<< tileset.Name <<std::endl;

        std::string firstgid = xmlTileset->Attribute("firstgid", &tileset.FirstID);
        std::cout << "firstgid:"<< firstgid <<std::endl;

        std::string tilecount = xmlTileset->Attribute("tilecount", &tileset.TileCount);
        std::cout << "tilecount:"<< tilecount <<std::endl;

        tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;
        std::cout << "LastID:"<< tileset.LastID <<std::endl;

        std::string columns = xmlTileset->Attribute("columns", &tileset.ColCount);
        std::cout << "columns:"<< columns <<std::endl;

        tileset.RowCount = tileset.TileCount/tileset.ColCount;
        std::cout << "RowCount:"<< tileset.RowCount <<std::endl;

        std::string tilewidth = xmlTileset->Attribute("tilewidth", &tileset.TileSize);
        std::cout << "tilewidth:"<< tilewidth <<std::endl;

        TiXmlElement *image = xmlTileset->FirstChildElement();

        tileset.Source = image->Attribute("source");
        std::cout << "source:"<< tileset.Source << "\r\n" <<std::endl;
    #else
        xmlTileset->Attribute("firstgid", &tileset.FirstID);
        xmlTileset->Attribute("tilecount", &tileset.TileCount);
        tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;

        xmlTileset->Attribute("columns", &tileset.ColCount);
        tileset.RowCount = tileset.TileCount/tileset.ColCount;
        xmlTileset->Attribute("tilewidth", &tileset.TileSize);

        TiXmlElement *image = xmlTileset->FirstChildElement();
        tileset.Source = image->Attribute("source");
    #endif


    return tileset;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount){

    TiXmlElement *data;
    for(TiXmlElement *e=xmlLayer->FirstChildElement(); e!=nullptr; e=e->NextSiblingElement())
    {
        if(e->Value() == std::string("data"))
        {
            data = e;
            break;
        }
    }

    //parse layer tile map
    std::string matrix(data->GetText());
    std::istringstream iss(matrix);
    std::string id;
    TileMap tilemap(rowcount, std::vector<int>(colcount, 0));
    for(int row = 0; row < rowcount; row++){
        for(int col = 0; col < colcount; col++){
            std::getline(iss, id, ',');
            std::stringstream converter(id);
            converter >> tilemap[row][col];
            if(!iss.good()){break;}
        }
    }

    return (new TileLayer(tilesize, rowcount, colcount, tilemap, tilesets));
}


void MapParser::Clean(){
    std::map<std::string, GameMap*>::iterator it;
    for(it = m_MapDict.begin(); it != m_MapDict.end(); it++)
    {
        it->second = nullptr;
    }
    m_MapDict.clear();
}
























