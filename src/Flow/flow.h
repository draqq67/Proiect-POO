// for creating every flow i need to take several steps into account so in this approach i would use the builder creational pattern
#ifndef FLOW_H
#define FLOW_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
//interface for StepsBuilder
class FlowBuilder{
    
    public:
    virtual ~FlowBuilder() {}; 
};

//interface for the Steps
class FlowSteps
{
    public:
    virtual void printData() =0;
    virtual void setToFile( string file) =0;

};

//Text Related Steps and Builder
class TextRelatedSteps : public FlowSteps {
    
    public:
        vector<string> title;
        vector<string> subtitle;
        vector<string> flow_title;
        vector<string> text;
        vector<string> description;
        vector<string> text_input;
        
        void printData() override;
        void setToFile(string file) override;
};
class TextRelatedStepsBuilder : public FlowBuilder{
    private:
        TextRelatedSteps* text;
    public:
    ~TextRelatedStepsBuilder() override;
    TextRelatedSteps* getData();
    TextRelatedStepsBuilder();
    void addTitle(std::string title, std::string subtitle);
    void addText(std::string title, std::string copy);
    void addTextInput(std::string description, std::string input );
};

//Number Related Steps and Builder
class NumberRelatedSteps: public FlowSteps {
    
    public:
    vector<string> descriptions;
    vector<float> numbers;
    vector<string> calculus_description;
    vector<float> calculus;
        void printData() override;
        void setToFile(string file) override;
};
class NumberRelatedStepsBuilder : public FlowBuilder{

    private:
    NumberRelatedSteps* number;
    public :
    ~NumberRelatedStepsBuilder() override;
    NumberRelatedSteps* getData();
    NumberRelatedStepsBuilder();
    void numberInputStep(std::string description, float number );
    void calculusStep(std::vector<int> steps_index, std::vector<string> operators,std::string descriptions, std::vector<string> min_max,std::vector<string> just_operators);
    // void showCalculusStep();
    float operations(float a, float b, string operation);

};

//Display Steps and Builder
class DisplaySteps : public FlowSteps {
    public:
    vector<string> txtFileName;
    vector<string> csvFileName;
    vector<string> descriptionTxt;
    vector<string> descriptionCsv;
    void printData() override;
    void setToFile( string file) override;
};
class DisplayStepsBuilder : public FlowBuilder{ 
    private:
    DisplaySteps* display;
    public:
    ~DisplayStepsBuilder() override;
    DisplaySteps* getData();
    DisplayStepsBuilder();
    void chooseAndDisplayStep(string index,TextRelatedStepsBuilder * textsteps, NumberRelatedStepsBuilder* numbersteps);
    void csvAndTxtStep(string description, string name,string path, bool ok);
};


#endif