#include "codec.h"

//

namespace ws
{
    bool encodeEvent(String &src, Event &dest);

    bool decodeEvent(Event &src, String &dest);

    EventQuery encodeEventQuery(String query);

    String decodeEventQuery(EventQuery query);

    //

    bool encodeEvent(String &src, Event &dest)
    {
        JsonDocument eventDoc;
        DeserializationError desResult = deserializeJson(eventDoc, src);

        if (desResult.code() == DeserializationError::Ok)
        {
            dest.name = eventDoc["name"].as<String>();
            dest.data.set(eventDoc["data"].as<JsonArray>());
            dest.query = encodeEventQuery(eventDoc["query"].as<String>());

            return true;
        }
        else
        {
            return false;
        }
    }

    bool decodeEvent(Event &src, String &dest)
    {
        JsonDocument eventDoc;
        eventDoc["name"] = src.name;
        eventDoc["data"] = src.data;
        eventDoc["query"] = decodeEventQuery(src.query);

        size_t exp = measureJson(eventDoc);
        size_t res = serializeJson(eventDoc, dest);

        return exp == res;
    }

    EventQuery encodeEventQuery(String query)
    {
        if (query.equals("Create"))
            return EventQuery::Create;
        else if (query.equals("Retrieve"))
            return EventQuery::Retrieve;
        else if (query.equals("Update"))
            return EventQuery::Update;
        else
            return EventQuery::Delete;
    }

    String decodeEventQuery(EventQuery query)
    {
        switch (query)
        {
        case EventQuery::Create:
            return "Create";
        case EventQuery::Retrieve:
            return "Retrieve";
        case EventQuery::Update:
            return "Update";
        case EventQuery::Delete:
            return "Delete";
        default:
            return "Delete";
        }
    }
}