FROM ubuntu:22.04

WORKDIR /app

# Install build dependencies
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    cmake \
    doxygen \
    graphviz \
    git \
    libssl-dev \
    python3-pip \
    rapidjson-dev \
    sqlite3

# Copy project dir into container
COPY . .

# Create build directory
RUN rm -rf build
RUN mkdir build
WORKDIR /app/build

# Build and run project
# RUN cmake .. -DCMAKE_BUILD_TYPE=Release
# RUN cmake --build .
# CMD ["./ClimateAnalysis"]
ENTRYPOINT ["/bin/bash"]