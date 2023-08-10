#include "globals.h"
#include "qforeach.h"
#include "qjsonobject.h"

#include <QFile>

bool Globals::isSet = false;
std::string Globals::hash = "";

int Globals::m_pId;
HANDLE Globals::m_handle;
HWND Globals::m_hWnd;
uint32_t Globals::m_baseAddress;

ScriptConfig *Globals::m_scriptConfig = new ScriptConfig();

std::vector<Spell*> Globals::Spells;

int Globals::m_userId = -1;
QString Globals::m_username = "";
QString Globals::m_email = "";
QString Globals::m_password = "";
int Globals::m_loginTimestamp = -1;
QString Globals::m_userSignature = "";
int Globals::m_authErrorCount = 0;
int Globals::m_authSuccessCount = 0;
int Globals::m_authTickCount = 0;
QJsonObject Globals::userObject;

std::vector<Input*> Globals::m_inputList;

void Globals::updateHotkeys()
{

}

Spell* Globals::getSpell(std::string value)
{
    for (Spell* spell : Spells)
    {
        if (QString::fromStdString(spell->name).toLower() == QString::fromStdString(value).toLower())
            return spell;
        else if (QString::fromStdString(spell->words).toLower() == QString::fromStdString(value).toLower())
            return spell;
    }

    return nullptr;
}

Spell* Globals::getSpell(int value)
{
    for (Spell* spell : Spells)
    {
        if (spell->itemId == value)
            return spell;
        else if (spell->id == value)
            return spell;
    }

    return nullptr;
}

bool Globals::UpdateSpells()
{
    QFile file("Data/spells.xml");
    if (!file.exists())
        return false;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QXmlStreamReader reader(&file);

        while (!reader.atEnd() && !reader.hasError())
        {
            if (reader.isStartElement() && reader.name().compare("vocation"))
            {
                Spell* spell = new Spell(reader);
                Spells.push_back(spell);
            }
            else
                reader.readNext();
        }
        file.close();

        return true;
    }

    return false;
}
