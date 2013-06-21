////////////////////////////////////////////////////////////////////
//
// CutyCapt - A Qt WebKit Web Page Rendering Capture Utility
//
// Copyright (C) 2003-2013 Bjoern Hoehrmann <bjoern@hoehrmann.de>
// Modifications by Sam Stelfox <sstelfox@bedroomprogrammers.net> (2013)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License version 3
// as published by the Free Software Foundation.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License version 3 as published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
////////////////////////////////////////////////////////////////////

#include <QtWebKit>

#if QT_VERSION >= 0x050000
#include <QtWebKitWidgets>
#endif

class CutyCapt;
class CutyPage : public QWebPage {
  Q_OBJECT

public:
  void setAttribute(QWebSettings::WebAttribute option, const QString& value);
  void setUserAgent(const QString& userAgent);
  void setAlertString(const QString& alertString);
  void setPrintAlerts(bool printAlerts);
  void setCutyCapt(CutyCapt* cutyCapt);
  QString getAlertString();

protected:
  QString chooseFile(QWebFrame *frame, const QString& suggestedFile);
  void javaScriptConsoleMessage(const QString& message, int lineNumber, const QString& sourceID);
  bool javaScriptPrompt(QWebFrame*, const QString&, const QString&, QString*);
  void javaScriptAlert(QWebFrame*, const QString& msg);
  bool javaScriptConfirm(QWebFrame* frame, const QString& msg);
  QString userAgentForUrl(const QUrl& url) const;
  QString mUserAgent;
  QString mAlertString;
  bool mPrintAlerts;
  CutyCapt* mCutyCapt;
};

class CutyCapt : public QObject {
  Q_OBJECT

public:

  // TODO: This should really be elsewhere and be named differently
  enum OutputFormat { SvgFormat, PdfFormat, PsFormat, InnerTextFormat, HtmlFormat,
    RenderTreeFormat, PngFormat, JpegFormat, MngFormat, TiffFormat, GifFormat,
    BmpFormat, PpmFormat, XbmFormat, XpmFormat, OtherFormat };

  CutyCapt(CutyPage* page,
           const QString& output,
           int delay,
           OutputFormat format,
           const QString& scriptProp,
           const QString& scriptCode,
           bool insecure);

private slots:
  void DocumentComplete(bool ok);
  void InitialLayoutCompleted();
  void JavaScriptWindowObjectCleared();
  void Timeout();
  void Delayed();
  void handleSslErrors(QNetworkReply* reply, QList<QSslError> errors);

private:
  void TryDelayedRender();
  void saveSnapshot();
  bool mSawInitialLayout;
  bool mSawDocumentComplete;

protected:
  QString      mOutput;
  int          mDelay;
  CutyPage*    mPage;
  OutputFormat mFormat;
  QObject*     mScriptObj;
  QString      mScriptProp;
  QString      mScriptCode;
  bool         mInsecure;
};
