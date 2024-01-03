// for creating every flow i need to take several steps into account so in this approach i would use the builder creational pattern
#ifndef FLOW_H
#define FLOW_H
#include <iostream>
#include <string>

class FlowSteps{

    public:
    std::string text;
    std::string title;
    std::string subtitle;
    std::string description;
    std::string copy;
    virtual void listFlow()=0;
};
class FlowBuilder{
    
    public:
    virtual ~FlowBuilder() {}; 
    virtual void reset() = 0;
};
class TextRelatedSteps : public FlowSteps{

};
class TextRelatedStepsBuilder : public FlowBuilder{
    private:
    TextRelatedSteps* text;
    public:
    ~TextRelatedStepsBuilder() override;
    void reset() override;
    void addTitle(std::string title, std::string subtitle);
    void addText(std::string text, std::string copy);
    void addTextInput(std::string description, std::string input );
};
class NumberRelatedSteps : public FlowSteps{

};
class NumberRelatedStepsBuilder : public FlowBuilder{

    private:
    NumberRelatedSteps* step;
    public :
    ~NumberRelatedStepsBuilder() override;
    void reset() override;
    void numberInputStep(std::string description, float number );
    void calculusStep(int steps, std::string operation );
    void showCalculusStep();

};

class DisplaySteps : public FlowSteps{

};
class DisplayStepsBuilder : public FlowBuilder{ 
    private:
    DisplaySteps* display;
    public:
    ~DisplayStepsBuilder();
    void reset() override;
    void chooseAndDisplayStep();
    void txtStep();
    void csvStep();
};
class OutputSteps : public FlowSteps{

};
class OutputStepsBuilder : public FlowBuilder
{
    private:
    OutputSteps* output;
    public :
    ~OutputStepsBuilder();
    void reset() override;
    void generateTextFileStep();
    void provideDataStep();
    void generatingTimeStamp();
    void addInsights();
    void refreshInsights();

};

// the class where i get all the steps to build the flows
class Flow{

    public:
    void buildFlow();
    void createNewFlow();
    void accessExistingFlows(std::string username, std::string flowname );
    void deleteFlows();
};

#endif