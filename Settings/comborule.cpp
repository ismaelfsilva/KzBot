#include "comborule.h"
#include "globals.h"

ComboRule::ComboRule()
{
    leader = "";
    content = "";
    spellInput = "";
    itemId = 0;
    spell = nullptr;
}


bool ComboRule::Deserialize(QXmlStreamReader &reader)
{
    leader = "";
    content = "";
    spellInput = "";
    itemId = 0;
    spell = nullptr;

    if (!reader.attributes().value("id").isNull())
    {
        itemId = reader.attributes().value("id").toInt();
        spell = Globals::getSpell(itemId);
    }
    else if (!reader.attributes().value("spell").isNull())
    {
        spellInput = reader.attributes().value("spell").toString().toStdString();
        spell = Globals::getSpell(spellInput);
    }


    if (!reader.attributes().value("leader").isNull())
        leader = reader.attributes().value("leader").toString().toStdString();
    if (!reader.attributes().value("content").isNull())
        content = reader.attributes().value("content").toString().toStdString();

    return true;
}

bool ComboRule::Serialize(QXmlStreamWriter &writer)
{
    writer.writeStartElement("Combo");

    writer.writeAttribute("leader", leader);
    writer.writeAttribute("content", content);

    if (itemId > 0)
        writer.writeAttribute("id", QString::number(itemId));
    else
        writer.writeAttribute("spell", spellInput);

    writer.writeEndElement();

    return true;
}
