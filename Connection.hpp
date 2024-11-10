#pragma once

#include <stdio.h>
#include <string.h>

// Define a struct for holding server connection data
typedef struct {
    char serverName[50];
    char port[10];
} ServerData;

// Function declaration for establishing a network connection with the server
void connection(ServerData dataMap);


