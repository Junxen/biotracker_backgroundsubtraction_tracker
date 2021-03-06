#include "Config.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <QStringList>
#include <iostream>
#include <QFile>
#include <QDir>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <QStandardPaths>

template<typename Stream>
Stream &operator>>(Stream& s, QString& q)
{
    std::string tmp;
    s >> tmp;
    q = tmp.data();
	return s;
}

template<typename Stream>
Stream &operator<<(Stream& s, QString const& q)
{
	return s << q.toStdString();
}

void Config::load(QString dir, QString file)
{
    using namespace boost::property_tree;

    auto tree = ptree{};
    QDir d(dir);
    d.mkpath(dir);
    QFile fin(dir + "/" + file);

    if(!fin.exists()) 
    {       
        fin.open(QIODevice::ReadWrite);
        fin.close();
    }
    
    read_ini((dir + "/" + file).toStdString(), tree);

    Config* config = this;

    std::string globalPrefix = "General.";
    config->EnableView = tree.get<int>(globalPrefix+"EnableView",config->EnableView);
    config->EnableMove = tree.get<int>(globalPrefix+"EnableMove",config->EnableMove);
    config->EnableRemove = tree.get<int>(globalPrefix+"EnableRemove",config->EnableRemove);
    config->EnableSwap = tree.get<int>(globalPrefix+"EnableSwap",config->EnableSwap);
    config->EnableAdd = tree.get<int>(globalPrefix+"EnableAdd",config->EnableAdd);
    config->EnableRotate = tree.get<int>(globalPrefix+"EnableRotate",config->EnableRotate);
    config->BinarizationThreshold = tree.get<int>(globalPrefix+"BinarizationThreshold",config->BinarizationThreshold);
    config->SizeErode = tree.get<int>(globalPrefix+"SizeErode",config->SizeErode);
    config->SizeDilate = tree.get<int>(globalPrefix+"SizeDilate",config->SizeDilate);
    config->MinBlobSize = tree.get<int>(globalPrefix+"MinBlobSize",config->MinBlobSize);
    config->MaxBlobSize = tree.get<int>(globalPrefix+"MaxBlobSize",config->MaxBlobSize);
    config->Mog2History = tree.get<int>(globalPrefix+"Mog2History",config->Mog2History);
    config->Mog2VarThresh = tree.get<int>(globalPrefix+"Mog2VarThresh",config->Mog2VarThresh);
    config->Mog2BackgroundRatio = tree.get<double>(globalPrefix+"Mog2BackgroundRatio",config->Mog2BackgroundRatio);
    config->DoNetwork = tree.get<int>(globalPrefix+"DoNetwork",config->DoNetwork);
    config->NetworkPort = tree.get<int>(globalPrefix+"NetworkPort",config->NetworkPort);
    config->DoBackground = tree.get<int>(globalPrefix+"DoBackground",config->DoBackground);
    config->ResetBackground = tree.get<int>(globalPrefix+"ResetBackground",config->ResetBackground);
}

void Config::save(QString dir, QString file)
{
    using namespace boost::property_tree;

    auto tree = ptree{};
    Config *config = this;

    std::string globalPrefix = "General.";
    tree.put(globalPrefix+"EnableView", config->EnableView);
    tree.put(globalPrefix+"EnableMove", config->EnableMove);
    tree.put(globalPrefix+"EnableRemove", config->EnableRemove);
    tree.put(globalPrefix+"EnableSwap", config->EnableSwap);
    tree.put(globalPrefix+"EnableAdd", config->EnableAdd);
    tree.put(globalPrefix+"EnableRotate", config->EnableRotate);
    tree.put(globalPrefix+"BinarizationThreshold", config->BinarizationThreshold);
    tree.put(globalPrefix+"SizeErode", config->SizeErode);
    tree.put(globalPrefix+"SizeDilate", config->SizeDilate);
    tree.put(globalPrefix+"MinBlobSize", config->MinBlobSize);
    tree.put(globalPrefix+"MaxBlobSize", config->MaxBlobSize);
    tree.put(globalPrefix+"Mog2History", config->Mog2History);
    tree.put(globalPrefix+"Mog2VarThresh", config->Mog2VarThresh);
    tree.put(globalPrefix+"Mog2BackgroundRatio", config->Mog2BackgroundRatio);
    tree.put(globalPrefix+"DoNetwork", config->DoNetwork);
    tree.put(globalPrefix+"NetworkPort", config->NetworkPort);
    tree.put(globalPrefix+"DoBackground", config->DoBackground);
    tree.put(globalPrefix+"ResetBackground", config->ResetBackground);

    write_ini((dir + "/" + file).toStdString(), tree);
}
