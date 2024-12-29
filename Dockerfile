# Use an official GCC image as a parent image
FROM gcc:latest

# Set the working directory in the container
WORKDIR /usr/src/app

# Copy the current directory contents into the container at /usr/src/app
COPY . .

# Install dependencies
RUN apt-get update && apt-get install -y sqlite3 libsqlite3-dev

# Compile the C++ program
RUN g++ -o main main.cpp -lsqlite3 -lstdc++fs

# Make port 80 available to the world outside this container
EXPOSE 80

# Run the executable
CMD ["./main", "/path/to/directory"]