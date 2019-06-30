# Callback Functions Registration

## Introduction

This project is a sample code to create a program to accept the functions from clients and run them asynchronizedly.

The program is to fulfill the goals: <br>
1\. The server side will be running all the time. <br>
2\. It accepts the functions from the requests and register them. The number of functions to be registered is limited: If there are functions to be registered more than the limit of server, the server will drop them and return the status code (503). <br>
3\. There is an event which will be triggered on the server side perodically. <br>
4\. When the event is not triggered, the functions will be kept on the server side and not called. <br>
5\. When the event is triggered, the server side will call the functions during a fix length of time period. (Here, we set this period to be 1s.) <br>
4\. At the time when the event is triggered, the server can still accept functions to be registered and call the functions asap.

## Program Organization
