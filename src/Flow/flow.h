// for creating every flow i need to take several steps into account so in this approach i would use the builder creational pattern
#ifndef FLOW_H
#define FLOW_H
#include <iostream>
#include <string>
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
    // virtual void setToFile() =0;

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
        // void setToFile() override;
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
class NumberRelatedSteps{
    
    // public:
    //     void printData() override;
    //     void setToFile() override;
};
class NumberRelatedStepsBuilder : public FlowBuilder{

    private:
    NumberRelatedSteps* number;
    public :
    ~NumberRelatedStepsBuilder() override;
    NumberRelatedSteps* getData();
    NumberRelatedStepsBuilder();
    void numberInputStep(std::string description, float number );
    void calculusStep(int steps, std::string operation );
    void showCalculusStep();

};

//Display Steps and Builder
class DisplaySteps{
    // void printData() override;
    // void setToFile() override;
};
class DisplayStepsBuilder : public FlowBuilder{ 
    private:
    DisplaySteps* display;
    public:
    ~DisplayStepsBuilder() override;
    DisplaySteps* getData();
    DisplayStepsBuilder();
    void chooseAndDisplayStep();
    void txtStep();
    void csvStep();
};
//Output Steps And Builder
class OutputSteps{
    
    // public:
    //     void printData() override;
    //     void setToFile() override;
};
class OutputStepsBuilder : public FlowBuilder
{
    private:
    OutputSteps* output;
    public :
    ~OutputStepsBuilder();
    OutputSteps* getData();
    OutputStepsBuilder();
    void generateTextFileStep();
    void provideDataStep();
    void generatingTimeStamp();
    void addInsights();
    void refreshInsights();

};

#endif