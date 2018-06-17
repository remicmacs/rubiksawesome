# Project

This file explain how we managed the project and tried to deliver the best possible piece of work we could come up with.



## Kickoff

The first order of business has been to brainstorm on the topic of the assignment. 

### Tools

We first decided to discuss project planning and tools.

We agreed on :

* Using git, so as to learn more about it along the way ;
* Have a precise documentation of the project, in English ;
* Use a code beautifier rather than having debates on code formatting ;
* Try to use unit tests and pair programming on difficult tasks ;
* Contenerize the final app to simplify deployment

We only stick to git and documentation eventually. Unfortunately, developer tool s for the C language demand a high time investment to master. Thus the `indent` code beautifier was considered but we did not find the time to investigate further. We tried some Unit Testing Frameworks (CUnit, Unity), but it was also complicated to find a setup that could work as quickly and smoothly for everybody in the team, without having anyone knowing the framework.

For this project, we focused on using and maintaining a GitLab server for version control, and on quality documentation and comments. We learned a great deal on three tools : git, make and OpenGL. We agreed that too much tools to learn and master is too intensive for one project, and we should learn new tools progressively. For instance we could add only one tool by project, only when we are comfortable with the previously added ones.

#### GitLab server

![GitLab logo](docs/img/GitLabLogo.png)

Alexandre installed and hosted a GitLab instance on his personnal domain. He learned more about containers, orchestration, server configuration and maintenance.

**Rancher** was used on the server as a container management system. The server had some problems with a memory leak that forces to reboot once every few days. Sometimes we had performances issues and server errors, and Alexandre spent a lot of time fixing it. He gained experience on how containers works as well as Rancher.

We all had experience with Git version control before, but often it was with small teams or only on repository on which we were the sole maintainer. This project was the opportunity to try-out the [**feature-branch workflow]**(https://www.atlassian.com/git/tutorials/comparing-workflows/feature-branch-workflow). This workflow is based on the principle that every knew feature should be developed and tested on its own branch, with the branch `master` reserved only for stable versions. We are know all accustomed to do merges, branches, stashes, resolving conflicts .

But far from a simple git server instance, GitLab offered us the opportunity to use its integrated project management. It has its own Kanban-like board where all tasks can be displayed. We can also open issues that can be tagged with keywords, being a bux fixing request, a feature request, etc. We use those tools for task repartition during our project.

## Distribution of tasks

We allocated the responsibilities according each member of the group's experience :

* Alexandre has an expertise in competitive Rubik's Cube solving (speedcubing) and is therefore in charge of the solving algorithm ;
* Rodolphe has been regularly working with 3D fameworks and is used to draw and animate shapes in a 3D environment. He has consequently been put in charge of the graphical display of the project ;
* Rémi has already implemented some application with groups of two to six developers, and has been put in charge of the design of the core logic of the application.

The main motive to this organization was that we could not find a lot of time to progress on an aspect of the application while waiting for somebody's code. Thus, it was preferable if Rodolphe could focus each on his responsibility. Rémi was there to assemble the different pieces of the project together, and implement whatever functionality the other could need. With this position,  Rémi was to keep an eye on the big picture and how all the parts of the code work together, while Rodolphe and Alexandre were to focus on really technical issues.

## Design choices

### Data representation

The state of the data is essential for this application. Each step of the program depends on pattern, whether the game has reached an endgame, or if the solving algorithm can find a way to progress towards specific patterns.

We decided to split the data representation in two parts. One would hold all the color values on a 2D die pattern. The other would not be used to track color state, but to track the position of the objects in three dimensional space.

The choice was motivated by the need to have a data model on which test solving algorithm without depending on the 3D representation.  That way, progress on the solving and on the 3D view could be made simultaneously.

Rémi focused first on creating a data structure holding all necessary information to allow solving algorithm testing. The main objective was to have a public interface to manipulate this data without corrupting it or taking risks with direct access.

Then Rodolphe created and modified along the way the data structure holding pointers to 3D objects necessary for the animations and display.



#### Public interface for data manipulation

Since the Rubik's Cube is limited to a certain amount of moves, and considering the existing conventions on movements naming in the speedcubers community, we chose to implement only moves used by resolution algorithms. The details can be found in [`MODEL.md`](MODEL.md) but the essential idea was to design a cube data structure that would be only mutable via the 6 basic rotations (**F**ront, **B**ack, **R**ight, **L**eft, **U**p, **D**own) and the 3 axis orientations (**x, y, z**), and their complementary moves.



### Event dripping and bubbling

We chose to follow a MVC (Model View Controller) design pattern, because it appeared to be a good idea with a project this complex.

* The Model holds all data and state information about the current instance of the program ;
* The View is the part of the program that is in charge of interaction and display with the user ;
* The controller checks all data flow problems, decide whatever to do with all the information gathered and stored by the rest of the program.

Here is a diagram to show how events are dripping from the view to the controller and the data, before bobbling up again after the input and command validation.

![Events dripping and bubbling](docs/img/events_diag.png)



We can see that SDL has a role that is not strictly speaking _View_ responsibilities. Is because SDL is a framework providing a lot of _Controller_-like logic to handler user interaction, window management, and so on.



### Core logic

The role of the controller is to facilitate data manipulation and communication between the view and the model. All data validity control and data workflow should be assessed by the controller. To be able to do so, we implemented a lot of utilities, for both production and debugging purposes. For instance, the utility function`printMoveQueue()` has been implemented to ease the debug process by displaying the contents of the `mvqueue` data structure. However the `mvqueue` and `mvstack` data structures are very much part of the production code, to transfer lists of moves between the controller and the display logic.

To have more informations on core logic implementations, the reader should refer to [`CONTROLLER.md`](CONTROLLER.md). 