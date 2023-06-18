# LarsonView



## Purpose

LarsonView is a website that allows users to remotely check the availability of laundry machines in Larson Hall through a real-time dashboard. This work was supported by an $800 entrepreneurial grant from the Piper Center. You can access the website [here](https://larsonview.com).

![website](https://raw.githubusercontent.com/radall1/LarsonView/main/images/demo.png)

## How does this work?

There are Raspberry Pis, connected to the washing machines in Larson Hall, that measure the current intensity being consumed by each individual washer. It emits that data through an algorithm that determines if it is available or occupied. Then, the Raspberry Pis update a cloud-based database that stores the status of each washer machine (code will be provided later).

The code currently available in this repository represents the Node.js application that queries information from that database and displays it to the users. 

## One more thing

This project was influenced by 3 different St. Olaf courses. The idea was born in PHYS 160: Intro to Engineering Design (using Arduino boards), the implementation blueprint was attempted in CS 251: Software Design and then finally, the switch to Raspberry Pis happened after getting introduced to them in CS 241: Hardware Design. 

All this to say: the `/sd_project` directory contains the CS 251: Software Design primitive implementation of this project which was very different (using Arduino boards, C++ and no database) and unrelated to how it currently works. It exists primarily for nostalgia purposes now. 