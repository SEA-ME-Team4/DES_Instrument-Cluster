# **DES Project - Instrument Cluster**
## PiRacer instrument cluster Qt application running on RPi and receiving speed data from a speed sensor via CAN  
</br>

## Architecture

<p align="center"><img src="Documents/DES02 Architecture Transparent.svg" alt="Alt text" width="70%" height="70%" /></p>


# Index
#### HW Setting.
#### Cross Compiling
#### [Introduction](#introduction-1)
#### [Background Information](#background-information-1)
#### [Project Goals & Objectives](#project-goals-and-objectives)
#### [Technical Requirements](#technical-requirements-1)
#### [System Architecture](#system-architecture-1)
#### [Software Design](#software-design-1)
#### [Implementation](#implementation-1)
#### [Project Timeline](#project-timeline-1)
#### [Collaboration and Teamwork](#collaboration-and-teamwork-1)
#### [Mentorship and Support](#mentorship-and-support-1)
#### [Reflection and Self-Assessment](#reflection-and-self-assessment-1)
#### [Results](#results-1)
#### [Submission](#submission-1)
#### [References](#references-1)
</br>

# Introduction

The PiRacer instrument cluster Qt application project is aimed at creating a real-time speedometer for a racing car. The application will run on a Raspberry Pi and receive speed data from a speed sensor via the Controller Area Network (CAN) protocol. This project will provide an opportunity for students to gain practical experience in software engineering, specifically in the areas of embedded systems, software architecture, and communication protocols. The project will also allow students to apply their knowledge of the Qt framework, which is widely used in the automotive industry for developing embedded applications. The successful completion of this project will demonstrate the students' ability to design and implement a real-world software solution, and their ability to effectively communicate their results.  
</br>


# Background Information

This section would provide background information on the technologies and tools used in the project, including the Raspberry Pi, Qt framework, and CAN (Controller Area Network) protocol.

The Raspberry Pi is a small, low-cost computer that is commonly used for hobbyist and educational projects. It provides a versatile platform for developing a wide range of applications, including those in the automotive industry. The Qt framework is a popular cross-platform application development framework that is widely used in the automotive industry for developing embedded applications, such as instrument clusters and infotainment systems. The CAN protocol is a communication standard that is widely used in the automotive industry for interconnecting different electronic control units in a vehicle.

In this project, the students will use the Raspberry Pi as the platform for the instrument cluster application, and the Qt framework for the user interface and data processing. The speed data will be received from a speed sensor via the CAN bus, and displayed in real-time on the instrument cluster application. The use of the Raspberry Pi and Qt framework, combined with the CAN protocol, will provide students with an understanding of the key technologies and tools used in the automotive industry for developing embedded systems. Additionally, the project will allow students to gain practical experience in software engineering, specifically in the areas of embedded systems, software architecture, and communication protocols.  
</br>


# Project Goals and Objectives

The main goal of the PiRacer Instrument Cluster Qt Application project is to create a functioning instrument cluster for a racing car that displays real-time speed data from a speed sensor via CAN bus.

The following are the specific objectives of the project:

1. To design and implement a Qt-based graphical user interface (GUI) for the instrument cluster.
2. To integrate a speed sensor with the Raspberry Pi using the CAN bus protocol.
3. To display real-time speed data on the instrument cluster GUI.
4. To test the functionality of the instrument cluster using realistic racing scenarios.
5. To document the project in a comprehensive manner, including a detailed explanation of the system architecture, software design, implementation, results, and conclusions.

By meeting these objectives, the project will demonstrate the ability to use software engineering techniques to create a functional and user-friendly instrument cluster for a racing car.  
</br>


# Technical Requirements

1. Raspberry Pi: The Raspberry Pi is a small, low-cost, single-board computer that is ideal for developing and testing embedded applications. A Raspberry Pi 3 Model B or later is recommended for this project, as it provides sufficient processing power and memory for running the instrument cluster application and receiving data from the speed sensor via CAN.

2. Qt Creator and the Qt libraries for Raspberry Pi: Qt Creator is a powerful, cross-platform integrated development environment (IDE) for developing applications with the Qt framework. The Qt libraries for Raspberry Pi include all of the necessary components for building Qt applications for the Raspberry Pi.

3. CAN bus interface: A CAN bus interface is required for connecting the Raspberry Pi to the vehicle's CAN bus and receiving speed data from the speed sensor. Suitable CAN bus interfaces for the Raspberry Pi include the MCP2515 and the TJA1050.

4. Speed sensor: A speed sensor capable of transmitting speed data via CAN is required for this project. The type of speed sensor required will depend on the vehicle being used for testing.

5. OBD-II cable: An OBD-II cable is required for connecting the Raspberry Pi and the speed sensor to the vehicle's CAN bus. This cable provides a convenient and reliable way to tap into the vehicle's CAN bus and receive data from the speed sensor.

6. Voltage regulator: A 12V to 5V voltage regulator is required for powering the Raspberry Pi from the vehicle's electrical system. The voltage regulator ensures that the Raspberry Pi receives a stable, regulated power supply, even when the vehicle's electrical system voltage fluctuates.

7. Display: A display is required for the instrument cluster application. Suitable displays include LCD and OLED displays, and the size and resolution of the display will depend on the specific requirements of the instrument cluster application.

8. Mounting hardware: A suitable method of mounting the display and Raspberry Pi in the vehicle is required. This may involve mounting brackets, enclosures, or other hardware, depending on the specific requirements of the instrument cluster application.

9. Vehicle for testing: Access to a vehicle for testing the instrument cluster application is required. The vehicle should have a CAN bus system and should be compatible with the speed sensor and other hardware components.

The students will be responsible for sourcing all of the required hardware components and ensuring that the hardware is compatible with the Raspberry Pi and the CAN bus interface. They will also be responsible for installing and configuring the operating system, the Qt framework, and any necessary drivers or libraries. The students will need to write and test the instrument cluster application, including the user interface, data processing, and CAN communication code. They will also need to integrate the application with the hardware components and test the instrument cluster in a vehicle. Finally, the students will be expected to document their work and demonstrate the instrument cluster application in a final presentation. This project requires a solid understanding of software development and embedded systems, as well as the ability to work effectively in a team and to solve complex technical problems.  
</br>


# System Architecture

The system architecture of the PiRacer instrument cluster application is a combination of hardware and software components that work together to provide a user-friendly interface for monitoring the speed of the vehicle. The hardware components include a Raspberry Pi (RPi) board, a speed sensor, and a Controller Area Network (CAN) bus. The software component is a Qt-based application that runs on the RPi and communicates with the speed sensor via the CAN bus to receive speed data.

The RPi serves as the main processing unit for the instrument cluster application and is responsible for displaying the speed data on its screen. The speed sensor measures the speed of the vehicle and sends this data to the RPi via the CAN bus. The Qt application on the RPi receives this data and displays it in an easy-to-read format on the screen.

The CAN bus is a communication protocol that allows multiple devices to communicate with each other and exchange data. In the case of the PiRacer instrument cluster, the speed sensor and the RPi use the CAN bus to exchange speed data. The CAN bus provides a reliable and efficient way of transmitting data between the speed sensor and the RPi.

Overall, the system architecture of the PiRacer instrument cluster application is designed to provide a simple and user-friendly interface for monitoring the speed of the vehicle. The combination of hardware and software components work together to provide accurate and real-time speed data to the user.  
</br>


# Software Design

The software design of the PiRacer instrument cluster application is based on the Qt framework, which is a popular cross-platform application development framework. Qt provides a wide range of tools and libraries that make it easy to create user-friendly graphical user interfaces (GUIs) and communicate with hardware devices.

The software design of the PiRacer instrument cluster consists of several key components, including the main application, the CAN communication module, and the speed data display module.

The main application is responsible for managing the overall functionality of the instrument cluster. It creates the GUI, manages the communication with the speed sensor via the CAN bus, and displays the speed data on the screen.

The CAN communication module is responsible for communicating with the speed sensor via the CAN bus. It receives speed data from the speed sensor and passes it on to the main application for display. This module uses the CAN library provided by Qt to communicate with the speed sensor.

The speed data display module is responsible for displaying the speed data on the screen. It receives speed data from the main application and displays it in an easy-to-read format on the screen. This module can be customized to display the speed data in various ways, such as using a speedometer or a numerical display.

The software design of the PiRacer instrument cluster application is designed to be flexible and scalable, allowing for future modifications and additions. The use of the Qt framework and modular design also makes it easy to maintain and update the application. Overall, the software design of the PiRacer instrument cluster application is designed to provide a user-friendly and efficient interface for monitoring the speed of the vehicle.  
</br>


# Implementation

The implementation of the PiRacer instrument cluster application involves several key steps, including writing the code for the various components, testing the code, and deploying the application on the Raspberry Pi.

1. Writing the code: The first step in the implementation process is writing the code for the various components of the application. This includes writing the code for the main application, the CAN communication module, and the speed data display module. The code should be written in a clear and organized manner, making use of best practices in software engineering.

2. Testing the code: After writing the code, it is important to test it to ensure that it works correctly and meets the technical requirements. This can be done by running the code on the Raspberry Pi and verifying that it correctly receives speed data from the speed sensor and displays it on the screen.

3. Deploying the application: Once the code has been tested and verified, the application can be deployed on the Raspberry Pi. This involves copying the code to the Raspberry Pi and executing it. The Raspberry Pi should be configured to boot up and run the application automatically upon startup.

The implementation process should be carefully planned and executed to ensure that the final product meets the technical requirements and provides a user-friendly interface for monitoring the speed of the vehicle. The implementation process should also be carefully documented, so that any future modifications or updates to the application can be made easily.

Overall, the implementation of the PiRacer instrument cluster application involves several key steps, including writing the code, testing the code, and deploying the application on the Raspberry Pi. The implementation process should be carefully planned and executed to ensure that the final product meets the technical requirements and provides a user-friendly interface for monitoring the speed of the vehicle.  
</br>


# Project Timeline

The PiRacer Instrument Cluster Qt Application project is expected to take approximately 6-8 weeks to complete, with the following estimated timeline:

* Week 1-2:
  * Research and familiarization with the CAN bus protocol, speed sensors, and Qt.
  * Design of the system architecture and software design.

* Week 3-4:
  * Implementation of the Qt-based GUI for the instrument cluster.
  * Integration of the speed sensor with the Raspberry Pi using the CAN bus protocol.

* Week 5-6:
  * Testing and debugging of the instrument cluster.
  * Verification of real-time speed data display on the instrument cluster GUI.

* Week 7-8:
  * Final documentation and report writing, including a detailed explanation of the system architecture, software design, implementation, results, and conclusions.
  * Preparation for final presentation and demonstration.

Note: This timeline is an estimate and may change based on the actual progress and complexities encountered during the project. The project team will regularly review the timeline and make adjustments as necessary to ensure the project is completed on time and within scope.  
</br>


# Collaboration and Teamwork

Students will be working in teams of maximum four to complete this project. Each team member will be assigned specific tasks and responsibilities, and will be expected to contribute to the overall success of the project. Teams will be required to submit regular progress reports and to meet with the instructor for check-ins and feedback.  
</br>


# Mentorship and Support

Students will be provided with mentorship and support from the instructor throughout the project. The instructor will be available for questions and guidance, and will hold regular check-ins and progress reports to provide feedback and support.  
</br>


# Reflection and Self-Assessment

Students will be encouraged to reflect on their own learning and progress throughout the project. This will be done through self-assessment exercises and through feedback from the instructor and other team members.  
</br>


# Results

The results of the PiRacer instrument cluster application can be evaluated based on the following factors:

1. Functionality: The most important factor in evaluating the results of the project is the functionality of the application. Does the application receive speed data from the speed sensor via CAN and display it on the screen in a user-friendly manner? If the answer is yes, then the application can be considered a success.

2. Usability: Another important factor in evaluating the results of the project is the usability of the application. Is the application user-friendly and easy to use? Does it provide a clear and intuitive interface for monitoring the speed of the vehicle? If the answer is yes, then the application can be considered a success.

3. Reliability: The reliability of the application is another important factor in evaluating the results of the project. Does the application run smoothly and consistently without any errors or crashes? If the answer is yes, then the application can be considered a success.

4. Maintainability: The maintainability of the application is another important factor in evaluating the results of the project. Is the code well-organized and easy to modify? Can future updates and modifications be made easily? If the answer is yes, then the application can be considered a success.

Overall, the results of the PiRacer instrument cluster application can be evaluated based on the functionality, usability, reliability, and maintainability of the application. If the application meets the technical requirements and provides a user-friendly interface for monitoring the speed of the vehicle, it can be considered a success.  
</br>


# Submission

Turn in a github repository with following information:

1. Code and relevant configuration files.

2. Detailed descriptions of algorithms and data structures used in the implementation.

3. Screenshots and diagrams of the instrument cluster user interface.

4. Detailed test plans, test cases, and results of software testing and debugging.

5. Detailed descriptions of the hardware components used in the project, including the Raspberry Pi and the speed sensor.

6. A list of online resources and tutorials used in the project.

7. Any additional material that supports the understanding of the project and provides context to the reader.  

</br>


# References

1. Embedded Systems Design with the Raspberry Pi, by Muhammed Ali, Packt Publishing (2017)

2. The Qt Company (2021). Qt 5.15.0 Reference Documentation. Available at: https://doc.qt.io/qt-5/index.html

3. Bosch, R. (2016). Automotive Handbook (9th edition). Springer.

4. SAE International (2018). J1939 Digital Annex Document, Society of Automotive Engineers, Warrendale, PA.

5. CAN in Automation (CiA) e.V. (2017). CAN FD Specification Version 1.0.

6. K. Mäntylä, T. Mäntylä (2008). “Requirements Engineering Processes in the Automotive Domain.” Journal of Systems and Software, vol. 81, no. 11, pp. 19-29.

7. H. Elmqvist, B. Englund (2010). “Qt Quick and QML for N950”. Available at: https://www.slideshare.net/QtDevelopment/qt-quick-and-qml-for-n950

8. Raspberry Pi Foundation (2021). Raspberry Pi Hardware Reference. Available at: https://www.raspberrypi.org/documentation/hardware/raspberrypi/

9. R. Davis (2016). “Agile Estimating and Planning”. Prentice Hall.

10. I. Sommerville (2011). “Software Engineering”. Addison-Wesley.  

</br>



Shield: [![CC BY-NC-SA 4.0][cc-by-nc-sa-shield]][cc-by-nc-sa]

This work is licensed under a
[Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License][cc-by-nc-sa].

[![CC BY-NC-SA 4.0][cc-by-nc-sa-image]][cc-by-nc-sa]

[cc-by-nc-sa]: http://creativecommons.org/licenses/by-nc-sa/4.0/
[cc-by-nc-sa-image]: https://licensebuttons.net/l/by-nc-sa/4.0/88x31.png
[cc-by-nc-sa-shield]: https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-lightgrey.svg
