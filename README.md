# Proiect POO

An app that allows users to create custom flows for processes they use in their work.

I propose in this project to made an app customed to the requirments propose

## Firstly, my project consists into 3 cpps : 

main.cpp, user.cpp, flow.cpp

main.cpp -> I define the user and appeal the function user.greeting() to start the program 

### user.cpp: 
   -Firstly i get into a scene where i authentif and log in. I ve done this part because i wanted to store for each user the flows he s writting. I store them in FlowSystemDataBase/username/flows. UserBD is a csv with just the usernames as i didnt want to get to complicated with it.
   -After i authentificate and log in, user get two choices : 
        -to create a flow
        -to run a flow.
    -Flow creating:
        - for this part i had done 9 switch cases where i appeal flow.cpp methods to create a flow as mentioned in the requirments.
### flow.cpp structure 
 - i ve done a creational template mainly based on Builder with some little modification
 - I create an abstract class FlowBuilder that is an interface for : 
  - TextRelatedStepsBuilder for the texts related steps (Title,Text,Text Input)
  - NumberRelatedStepsBuilder for number related steps (Number and Calculus)
  - DisplayRelatedStepsBuilder for display related steps (chooseAndDisplay, csvandTextInputFilesStep)
  - The products from the subclasses of the Builder are defined on the abstract class flowSteps that have, they get the data from the builder through getData method:
  -TextRelatedSteps, NumberRelatedSteps, DisplayRelatedSteps that all have the prinData and sentToFile.
 -After i run all the flows. I get to 9th case where it is the output step where i appeal the method sendToFile from the products to create a flow file in the destined folder for each user  
### Run The Flow :
   - in user.cpp i have a method called accesingExistingFlows :
     - When that method is picked, the user gets a list of his flows to pick from.
     - the running scene is made by Run class where i call the methods upon to run the flow requsted. As i do run the flows, i will get slightly different analytics as requested in requirments.
     - The analytics would be :
         - Started : count how many times the flow has been started
         - Completed : count how many times the flow has been completed (0 errors, 0 skips)
         - Skips : how many times a step has been skipped
         - Error : count how many steps has not been completed 
         - AverageErrors/flow: average value of errors made per flow
      - When the user complete an action, he would type done, or undone if he doesn't finish it.
      - the analytics are stored per session in a class called Insights that changes them regarding to the rules and uploads them back in flow_stastistics
### Delete :

### Bugs :
   - calculus step : min/max can't take more than 2 arguments without failing, and also can take only up to one min/max per step
   - calculus step do to the nature of the if clauses it can take also arguments like step 0 step 1 step 2 / and still compute
   - not much of an issue but for csv&text input step the path starts as Proiect-Poo/ and don t have time to test if u take an argument like ../../path/to/smth/smth.txt if it can be read
