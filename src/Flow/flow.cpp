#include <iostream>
#include "flow.h"
#include <vector>
#include <string>
using namespace std;

// constructori si destructori initializati pentru fiecare clasa
TextRelatedStepsBuilder::~TextRelatedStepsBuilder()
{
    delete text;
}
TextRelatedStepsBuilder::TextRelatedStepsBuilder()
{
    this->text = new TextRelatedSteps();
}
NumberRelatedStepsBuilder::~NumberRelatedStepsBuilder()
{
    delete number;
}
NumberRelatedStepsBuilder::NumberRelatedStepsBuilder()
{
    this->number = new NumberRelatedSteps();
}
DisplayStepsBuilder::~DisplayStepsBuilder()
{
    delete display;
}
DisplayStepsBuilder::DisplayStepsBuilder()
{
    this->display = new DisplaySteps();
}
OutputStepsBuilder::~OutputStepsBuilder()
{
    delete output;
}
OutputStepsBuilder::OutputStepsBuilder()
{
    this->output = new OutputSteps();
}

// initializarea metodei de getData pentru fiecare obiectbuilder

TextRelatedSteps* TextRelatedStepsBuilder::getData()
{
    TextRelatedSteps* result = this->text;
    this->text = new TextRelatedSteps();
    return result;
}
NumberRelatedSteps* NumberRelatedStepsBuilder::getData()
{
    NumberRelatedSteps* result = this->number;
    this->number = new NumberRelatedSteps();
    return result;
}
DisplaySteps* DisplayStepsBuilder::getData()
{
    DisplaySteps* result = this->display;
    this->display = new DisplaySteps();
    return result;
}
OutputSteps* OutputStepsBuilder::getData()
{
    OutputSteps* result = this->output;
    this->output = new OutputSteps();
    return result;
}

// initializarea metodelor clasei TextRelatedSteps and Builder

void TextRelatedStepsBuilder::addTitle(string title, string subtitle)
{
    text->title.push_back(title);
    text->subtitle.push_back(subtitle);
}
void TextRelatedStepsBuilder::addText(string title, string copy)
{
    text->flow_title.push_back(title);
    text->text.push_back(copy);
}
void TextRelatedStepsBuilder::addTextInput(string description, string text_input)
{
    text->description.push_back(description);
    text->text_input.push_back(text_input);
}

void TextRelatedSteps::printData()
{
    for(int i = 0 ; i <title.size();i++)
        cout<<title[i]<<" ";
    
}
