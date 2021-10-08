#include "functions.h"
#include "QObject"
#include "QDebug"
#include "Windows.h"
//#include "WinUser.h"
#include "stdio.h"
#include "iostream"
#include "fstream"
#include "string"
#include "tchar.h"
#include <wchar.h>

//直接连接到User32.lib，qt里windowsAPI有时候除了头文件还要直接连接什么的
#pragma comment (lib,"User32.lib")

Functions::Functions(QObject *parent)
      :QObject(parent)
{

}

bool Functions::isFileExplorer(int x,int y)
{
    POINT pNow={x,y};
    HWND hwndPointNow = NULL;
    HWND Father = NULL;
    HWND Edit = NULL;
    CHAR	szClass[100];
    CHAR	FatherszClass[100];
    CHAR	EditszClass[100];
    TCHAR    Path[255];
    hwndPointNow = WindowFromPoint(pNow);  // 获取鼠标所在窗口的句柄
    GetClassNameA(hwndPointNow, szClass, 100);//获取句柄对应的类名

    Father = GetParent(hwndPointNow);
    GetClassNameA(Father, FatherszClass, 100);//获取句柄对应的类名
    if (_stricmp(FatherszClass, "SHELLDLL_DefView") == 0)
    {
        return true;
        Father = GetParent(Father);
        Father = GetParent(Father);
        Father = GetParent(Father);
        Father = GetParent(Father);
        Father = GetParent(Father);

        Edit = FindWindowEx(Father, NULL, TEXT("WorkerW"), NULL);
        Edit = FindWindowEx(Edit, NULL, TEXT("ReBarWindow32"), NULL);
        Edit = FindWindowEx(Edit, NULL, TEXT("Address Band Root"), NULL);
        Edit = FindWindowEx(Edit, NULL, TEXT("msctls_progress32"), NULL);
        Edit = FindWindowEx(Edit, NULL, TEXT("ComboBoxEx32"), NULL);
        Edit = FindWindowEx(Edit, NULL, TEXT("ComboBox"), NULL);
        Edit = FindWindowEx(Edit, NULL, TEXT("Edit"), NULL);

        GetClassNameA(Edit, EditszClass, 100);//获取句柄对应的类名

        SendMessage(Edit, WM_GETTEXT, 1024, (LPARAM)Path);
    }
    else
    {
        return false;
    }
}

std::string tchar2string(TCHAR* input)
{
    std::string output;
    try
    {
        int iLen = WideCharToMultiByte(CP_ACP, 0, input, -1, NULL, 0, NULL, NULL);

        char* chRtn = new char[iLen * sizeof(char)];

        WideCharToMultiByte(CP_ACP, 0, input, -1, chRtn, iLen, NULL, NULL);

        output = chRtn;
    }
    catch (std::exception e)
    {
    }

    return output;
}



int string_replase(std::string &s1, const std::string &s2, const std::string &s3)
{
    std::string::size_type pos = 0;
    std::string::size_type a = s2.size();
    std::string::size_type b = s3.size();
    while ((pos = s1.find(s2, pos)) != std::string::npos)
    {
        s1.replace(pos, a, s3);
        pos += b;
    }
    return 0;
}

std::string Functions::getPath(int x,int y,QString fileName)
{
    POINT pNow={x,y};
    HWND hwndPointNow = NULL;
    HWND Father = NULL;
    HWND Edit = NULL;
    CHAR	FatherszClass[100];
    TCHAR    Path[255];
    hwndPointNow = WindowFromPoint(pNow);  // 获取鼠标所在窗口的句柄

    Father = GetParent(hwndPointNow);//获取父窗句柄
    GetClassNameA(Father, FatherszClass, 100);//获取句柄对应的类名
    if (_stricmp(FatherszClass, "SHELLDLL_DefView") == 0)//如果父窗类名是SHELLDLL_DefView，那就是管理器
    {
        Father = GetParent(Father);
        Father = GetParent(Father);
        Father = GetParent(Father);
        Father = GetParent(Father);
        Father = GetParent(Father);

        Edit = FindWindowEx(Father, NULL, TEXT("WorkerW"), NULL);
        Edit = FindWindowEx(Edit, NULL, TEXT("ReBarWindow32"), NULL);
        Edit = FindWindowEx(Edit, NULL, TEXT("Address Band Root"), NULL);
        Edit = FindWindowEx(Edit, NULL, TEXT("msctls_progress32"), NULL);
        Edit = FindWindowEx(Edit, NULL, TEXT("ComboBoxEx32"), NULL);
        Edit = FindWindowEx(Edit, NULL, TEXT("ComboBox"), NULL);
        Edit = FindWindowEx(Edit, NULL, TEXT("Edit"), NULL);
        //最终定位到Edit

        SendMessage(Edit, WM_GETTEXT, 1024, (LPARAM)Path);//取得地址
        std::string path = tchar2string(Path);
        string_replase(path, "\\", "\\\\");
        path += "\\\\";
        std::string FileName = fileName.toStdString();
        path += FileName;
        path += ".txt";
        return path;
    }
    return "";
}


std::string stringToUnicode(const std::string &str)
{
    std::string unicodeStr;
    size_t length = strlen(str.c_str())+1;

    // char * setlocale ( int category, const char * locale );
    // 本函数用来配置地域的信息，设置当前程序使用的本地化信息.参数 locale 若是空字符串 ""，则会使用系统环境变量的 locale
    // 说明string中的字符编码是本机默认字符集，即GB字符集
    setlocale(LC_ALL,"");

    wchar_t wstr[33];
    mbstowcs(wstr, str.c_str(), length);
    char charUnicode[5];

    for (size_t i = 0; i < wcslen(wstr); i++) {
        memset(charUnicode, '\0', 5);
        unicodeStr.append(charUnicode);
    }

    return unicodeStr;
}

void Functions::saveFile(std::string path,QString text)
{
    //std::string Path=path.toStdString();
    std::string Text=text.toStdString();
    //std::string Path = stringToUnicode(path);
    /*
    QString QPath;
    QPath = QString(QString::fromLocal8Bit(path));
    QByteArray c_filename;
    c_filename = QPath.toLatin1();
    const char* filepath = c_filename.data();
    */
    std::ofstream outfile(path);
    if (outfile.is_open())
    {
        outfile << Text;
    }
    outfile.flush();
    outfile.close();
}
