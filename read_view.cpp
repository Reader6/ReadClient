#include "read_view.h"
#include<QDir>
#include<QDebug>
#include<QTextCodec>
#include <QSqlDatabase>
#include<QStandardPaths>
Read_View::Read_View(QObject *parent) : QObject(parent)
{
       m_currentBook=0;
       QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8")); // 改为GBK编码
       loadDir();
}


QQmlListProperty<Reader_Book> Read_View::books()
{
    return QQmlListProperty<Reader_Book>(this,this,
                            &Read_View::appendBooks,
                            &Read_View::booksCount,
                            &Read_View::booksAt,
                            &Read_View::clearBooks
                            );
}

int Read_View::booksCount()
{
    //qDebug() << "books:" << Book_shelf.count();
    return Book_shelf.count();
}

void Read_View::appendBooks(Reader_Book *chapter)
{
    Book_shelf.append(chapter);
}

Reader_Book *Read_View::booksAt(int index)
{
    if(index>=0 && Book_shelf.size()>index){
        qDebug() << Book_shelf.at(index);
        return Book_shelf.at(index);
    }else{
        return nullptr;
    }
}

void Read_View::clearBooks()
{
    for(int i=0;i<Book_shelf.count();i++){
        delete  Book_shelf[i];
    }
    Book_shelf.clear();
}

void Read_View::sorted()
{
    //排序
    return ;
}

int Read_View::currentBook()
{
    return m_currentBook;
}

void Read_View::setCurrentBook(int index)
{
    if(index==m_currentBook)return;
    m_currentBook=index;
    currentBookChanged(index);
}

void Read_View::loadDir(QString path)
{
    //path=QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).first();
    //path="/storage/emulated/0/book/";

    QDir Dir(path);

    if(!Dir.exists()){
        qDebug() << " error error path";
        return ;
    }else {
        qDebug() << path <<Dir.count();
    }

    for (unsigned i=0;i<Dir.count();i++) {
        loadBook(Dir.absolutePath()+"/"+Dir[i]+"/",Dir[i],i);
        //qDebug() << Dir[i];
    }
}
void Read_View::loadBook(QString path,QString name,int index)
{
    QDir Dir(path);
    if(!Dir.exists()){
        qDebug() << " error error path";
    }else {
        qDebug() << path;
    }
    QString temContent; //章节内容
    QString temName; //章节目录
    Reader_Book *temBook=new Reader_Book;
    for (unsigned i=0;i<Dir.count()-1;i++) {
          temName=Dir.absolutePath()+"/"+Dir[i]; //读取章节
          qDebug() << temName;
            // 问题？读取时只从文件名开头数字最小的开始读取，如开头为20和100，会先读取100
          Book_chapter *chapt=new Book_chapter(temName,Dir[i]); //把每本小说的所有章节的所在目录和章节名字一起放入chapt中
          temBook->appendChart(chapt);


    }
    temBook->setBookSource(path);
    temBook->setBookName(name);
    temBook->setindex(index);
    temBook->setimage(Dir.absolutePath()+"/"+name+".jpg");
    Book_shelf.append(temBook);
}



void Read_View::appendBooks(QQmlListProperty<Reader_Book> *list, Reader_Book *book)
{
    reinterpret_cast<Read_View*>(list->data)->appendBooks(book);
}

int Read_View::booksCount(QQmlListProperty<Reader_Book> *list)
{
    return  reinterpret_cast<Read_View*>(list->data)->booksCount();
}

Reader_Book *Read_View::booksAt(QQmlListProperty<Reader_Book> *list, int index)
{
    return reinterpret_cast<Read_View*>(list->data)->booksAt(index);
}

void Read_View::clearBooks(QQmlListProperty<Reader_Book> *list)
{
    return reinterpret_cast<Read_View*>(list->data)->clearBooks();

}

