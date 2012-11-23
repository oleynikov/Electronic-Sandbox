#ifndef GAMECONFIGURATION_H
#define GAMECONFIGURATION_H

#include <QString>
#include <QFile>
#include <QMap>
#include <QtXml/QXmlStreamReader>

#include <QDebug>

class Configuration
{

    public:
        static bool                     load(QString fileName = "configuration.xml")
        {

            QFile xmlConfigFile(fileName);
            if (!xmlConfigFile.open(QIODevice::ReadOnly|QIODevice::Text))
                return false;

            QXmlStreamReader xmlReader(&xmlConfigFile);

            while(!xmlReader.atEnd() && !xmlReader.hasError())
            {

                QXmlStreamReader::TokenType tokenType = xmlReader.readNext();

                if(tokenType == QXmlStreamReader::StartElement)
                {

                    if(xmlReader.name() == "parameter")
                    {

                        QString parameterName = xmlReader.attributes().value("name").toString();
                        QString parameterValue = xmlReader.attributes().value("value").toString();

                        Configuration::parameters.insert(parameterName,parameterValue);

                    }

                }

            }

            xmlReader.clear();
            xmlConfigFile.close();

            if(xmlReader.hasError())
                return false;

            return true;

        }
        static QString                  parameter(QString parameter)
        {

            return Configuration::parameters.find(parameter).value();

        }
        static QMap<QString,QString>    parameters;

};

#endif // GAMECONFIGURATION_H
