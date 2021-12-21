cmake_minimum_required(VERSION 3.18)

project(beej-tutorials VERSION 0.1 LANGUAGES C)

# first example
add_executable(showip beej_showip.c)

# client-server tcp example
add_executable(server beej_server.c)
add_executable(client beej_client.c)

# "client"-"server" udp example
add_executable(listener beej_listener.c)
add_executable(talker beej_talker.c)

