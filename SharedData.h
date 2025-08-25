#ifndef SHAREDDATA_H
#define SHAREDDATA_H

#include <QObject>
#include <string>

using namespace std;

class SharedData : public QObject
{
    Q_OBJECT

public:
    // 获取单例实例的静态方法
    static SharedData* getInstance()
    {
        static SharedData instance; // 静态局部变量，确保只创建一次
        return &instance;
    }

    // Getter 方法
    string searchStr() const { return m_searchStr; }
    string backgroundColor() const { return m_backgroundColor; }
    double picWidth() const { return m_picWidth; }
    double picHeight() const { return m_picHeight; }
    double picGap() const { return m_picGap; }
    double windowWidth() const { return m_windowWidth; }
    double windowHeight() const { return m_windowHeight; }
    int numPerLine() const { return m_numPerLine; }
    int maxPicNum() const { return m_maxPicNum; }

    // Setter 方法
    void setSearchStr(const string& searchStr) {
        if (m_searchStr != searchStr) {
            m_searchStr = searchStr;
            emit searchStrChanged(searchStr);
        }
    }
    void setBackgroundColor(const string& backgroundColor) {
        if (m_backgroundColor != backgroundColor) {
            m_backgroundColor = backgroundColor;
            emit backgroundColorChanged(backgroundColor);
        }
    }
    void setPicWidth(double picWidth) {
        if (m_picWidth != picWidth) {
            m_picWidth = picWidth;
            emit picWidthChanged(picWidth);
        }
    }
    void setPicHeight(double picHeight) {
        if (m_picHeight != picHeight) {
            m_picHeight = picHeight;
            emit picHeightChanged(picHeight);
        }
    }
    void setPicGap(double picGap) {
        if (m_picGap != picGap) {
            m_picGap = picGap;
            emit picGapChanged(picGap);
        }
    }
    void setWindowWidth(double windowWidth) {
        if (m_windowWidth != windowWidth) {
            m_windowWidth = windowWidth;
            emit windowWidthChanged(windowWidth);
        }
    }
    void setWindowHeight(double windowHeight) {
        if (m_windowHeight != windowHeight) {
            m_windowHeight = windowHeight;
            emit windowHeightChanged(windowHeight);
        }
    }
    void setNumPerLine(int numPerLine) {
        if (m_numPerLine != numPerLine) {
            m_numPerLine = numPerLine;
            emit numPerLineChanged(numPerLine);
        }
    }
    void setMaxPicNum(int maxPicNum) {
        if (m_maxPicNum != maxPicNum) {
            m_maxPicNum = maxPicNum;
            emit maxPicNumChanged(maxPicNum);
        }
    }

signals:
    void searchStrChanged(const string&);
    void backgroundColorChanged(const string&);
    void picWidthChanged(double);
    void picHeightChanged(double);
    void picGapChanged(double);
    void windowWidthChanged(double);
    void windowHeightChanged(double);
    void numPerLineChanged(int);
    void maxPicNumChanged(int);
    

private:
    // 私有构造函数，防止外部直接实例化
    explicit SharedData(QObject* parent = nullptr)
        : QObject(parent),
        m_searchStr(""),
        m_backgroundColor("#202020"),
        m_picWidth(80.0),
        m_picHeight(80.0),
        m_picGap(0.0),
        m_windowWidth(600.0),
        m_windowHeight(800.0),
        m_numPerLine(8),
        m_maxPicNum(10000)
    {
    }

    // 禁止拷贝构造和赋值操作
    SharedData(const SharedData&) = delete;
    void operator=(const SharedData&) = delete;

    // 成员变量
    string m_searchStr;
    string m_backgroundColor;
    double m_picWidth;
    double m_picHeight;
    double m_picGap;
    double m_windowWidth;
    double m_windowHeight;
    int m_numPerLine;
    int m_maxPicNum;
    bool m_imageCellPreviewIsVisible;
};

#endif // SHAREDDATA_H