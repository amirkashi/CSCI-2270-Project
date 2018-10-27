## Project Members:
* Amir Kashipazha
* Hamid Ashtiani

### Project summary:
For this project we obtained the 2012 climatological data for Boulder Municipal Airport from the National Climatic Data Center (NCDC). The data includes climatological information such as temperature, precipitation, wind speed, and wind direction. The goal of this project is to calculate the annual, monthly, daily, and hourly information for each data point.

### Program implementation:
Boulder Municipal Airport station records climate data three times per hour. The data we got for 2012 had 25,370 data. Due to the immense amount of data points, we decided to read in the data by the hour. To further explain, each node contained data information for each hour. This led each node to contain 3 data points. Since we inserted the data according to the recorded time, the format of the time was presented in the following order 2012MMDDHHMM.
The data points were inserted into a **red-black tree**. The reason we used a red-black tree was because our data was sequential. This would create a linked list which would increase run time and decrease efficiency. 

### System Requirement:
This application is able to run on either a Mac, Linux, or a Windows operating system.  

### Applications:
This program allows the user to examine any data for any city that is formatted in the same manner of the Boulder Municipal Airport station.
The data can be viewed in the project folder under the name “DataPRT.csv”.
