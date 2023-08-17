#include "rwfile.h"

RWFile::RWFile(QObject *parent) : QObject(parent)
{

}

bool RWFile::readConfInfo(ConfInfo &conf)
{
    string fileName = gQStr2Str(gCurrPath) + "/conf.txt";
    ifstream fin(fileName);
    if (!fin)
    {
        return false;
    }
    string line; //保存读入的每一行
    getline(fin, conf.superID);
    getline(fin, conf.superPwd);
    getline(fin, conf.order);
    getline(fin, conf.jysc);
    getline(fin, conf.znj);
    getline(fin, conf.wbTime);
    fin.close();
    return true;
}
bool RWFile::writeConfInfo(ConfInfo &conf)
{
    string fileName = gQStr2Str(gCurrPath) + "/conf.txt";
    ofstream fout(fileName);
    if (!fout)
    {
        return false;
    }
    fout << conf.superID << endl;
    fout << conf.superPwd << endl;
    fout << conf.order << endl;
    fout << conf.jysc << endl;
    fout << conf.znj << endl;
    fout << conf.wbTime << endl;
    fout.close();
    return true;
}

bool RWFile::readWBInfo(WBInfo &conf)
{
    string fileName = gQStr2Str(gCurrPath) + "/wb.txt";
    ifstream fin(fileName);
    if (!fin)
    {
        return false;
    }
    getline(fin, conf.wbStartTime);
    getline(fin, conf.wbStopTime);
    fin.close();
    return true;
}
bool RWFile::writeWBInfo( WBInfo &conf)
{
    string fileName = gQStr2Str(gCurrPath) + "/wb.txt";
    ofstream fout(fileName);
    if (!fout)
    {
        return false;
    }
    fout << conf.wbStartTime << endl;
    fout << conf.wbStopTime << endl;
    fout.close();
    return true;
}
