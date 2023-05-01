FROM osrf/ros:humble-desktop

# for gnu screen
ENV SHELL /bin/bash

RUN apt-get update && apt-get install -y \
    vim \
    git \
    wget \
    screen \
    terminator \
    && rm -rf /var/lib/apt/lists/*

RUN echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc \
    && /bin/bash -c "source ~/.bashrc"

RUN apt-get update && apt-get install -y \
    python3-colcon-common-extensions 
    
RUN mkdir -p ~/ros2_ws/src

COPY . /root/ros2_ws/src

RUN echo "source ~/ros2_ws/install/setup.bash" >> ~/.bashrc \
    && /bin/bash -c "source ~/.bashrc"
