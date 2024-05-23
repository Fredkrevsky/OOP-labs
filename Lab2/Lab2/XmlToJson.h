#pragma once
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "tinyxml2.h"

using json = nlohmann::json;
using namespace tinyxml2;

class XmlToJson {
public:
    static void convert(const std::string& inputFile, const std::string& outputFile) {
        tinyxml2::XMLDocument doc;
        if (doc.LoadFile(inputFile.c_str()) != XML_SUCCESS) {
            std::cerr << "Failed to load XML file." << std::endl;
            return;
        }

        json jsonData = json::array();
        XMLElement* root = doc.RootElement();
        xmlToJson(root, jsonData);

        std::ofstream ofs(outputFile);
        if (!ofs.is_open()) {
            std::cerr << "Failed to open output file." << std::endl;
            return;
        }
        ofs << jsonData.dump(4);
        ofs.close();
    }

private:
    static void xmlToJson(XMLElement* element, json& jsonArray) {
        if (!element) {
            return;
        }

        for (XMLElement* child = element->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
            json childJson;

            for (const XMLAttribute* attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next()) {
                std::string attrName = attr->Name();
                std::string attrValue = attr->Value();

                if (attrName == "type") {
                    childJson[attrName] = std::stoi(attrValue);
                }
            }

            for (XMLElement* grandchild = child->FirstChildElement(); grandchild != nullptr; grandchild = grandchild->NextSiblingElement()) {
                if (grandchild->GetText() != nullptr) {
                    std::string elementName = grandchild->Name();
                    std::string elementText = grandchild->GetText();

                    if (!elementText.empty() && elementText.front() == '"' && elementText.back() == '"') {
                        elementText = elementText.substr(1, elementText.size() - 2);
                    }
                    if (elementName == "fill_color" || elementName == "first_color" || elementName == "second_color") {
                        childJson[elementName] = json::parse(elementText);
                    }
                    else if (elementName == "height" || elementName == "outline_thickness" ||
                        elementName == "width" || elementName == "x" || elementName == "y") {
                        childJson[elementName] = std::stoi(elementText);
                    }
                    else if (elementName == "value") {
                        childJson[elementName] = std::stof(elementText);
                    }
                    else if (elementName == "isSelected") {
                        if (elementText == "false") {
                            childJson[elementName] = false;
                        }
                        else {
                            childJson[elementName] = true;
                        }
                    }
                    else {
                        childJson[elementName] = elementText;
                    }
                }
            }

            jsonArray.push_back(childJson);
        }
    }
};