# 12 Week Year C++ project

What this program should do, at minimum:

- Let the user write one goal for one day.
- choose one (yearly) tactic for that goal.
- choose the desired daily score for the tactic
- choose the daily score for the tactic 
- calculate the daily score (score/desired_score)
- save and retrieve all this info

objects:
- Goal: attributes: name, tactic 
        methods: give name, tactic

- Tactic: attributes: name, desired_score

- Day: attributes: Date, Tactic, score



As this is a quite complex program compared to what I'm used to, I will start by getting
the most simple version of the program to work, and then add functionalities as I go along.
The first program only has a 1 day year, with 1 goal and 1 tactic for that day. 

I learned how to do the most basic reading and writing from and to a file, and so I can load 
past data whenever I start the program. 

Now It's time to polish the basic version as far as possible, and after that begin adding some more
features, like many tactics for a goal, 7 day weeks and 12 week years.

Once the most basic program is done, I'll add the capacity to choose multiple tactics for the one
goal.


To save and load the information into the "data.txt" file, I will store it in this way:
+ [control] int vector containing the sizes of the data elements
        - Number of goals
        - Number of tactics of the first goal
        - Number of tactics of the second goal
        - ...

+ ["end_control"] string to indicate end of control part

+ [data] string vector containing the data
        - Name of 1st goal
        - Name of 2nd goal
        - ...
        - Name of tactic 1 of goal 1
        - Name of tactic 2 of goal 1
        - ...
        - Name of tactic 1 of goal 2
        - ...
        - Score of tactic 1 of goal 1
        - Score of tactic 2 of goal 1
        - ...
        - Score of tactic 1 of goal 2
        - ...