# Set the base image.
FROM alpine:latest

# Tag the repository.
LABEL org.opencontainers.image.source https://github.com/thepieterdc/mailbridge

################################################################################
################################### PACKAGES ###################################
################################################################################

# Install system packages.
RUN apk add --update --no-cache build-base curl-dev
RUN apk add --update --no-cache --virtual build-deps cmake

################################################################################
################################# APPLICATION ##################################
################################################################################

# Create a directory to store the application in.
RUN mkdir /app
WORKDIR /app

# Copy the application into the container.
COPY . /app

# Compile the application.
RUN cmake .
RUN make -j

################################################################################
#################################### CLEANUP ###################################
################################################################################

# Remove build dependencies.
RUN apk del build-deps

################################################################################
#################################### STARTUP ###################################
################################################################################

# Expose the server to the outside world.
EXPOSE 2525

# Start the application.
CMD ["./mailbridge"]