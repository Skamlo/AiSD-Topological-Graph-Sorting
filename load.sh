#!/bin/bash

# Function to validate integer input
validate_input() {
    if [[ $1 =~ ^[0-9]+$ ]]; then
        return 0
    else
        return 1
    fi
}

# Prompt user for number of nodes
read -p "Enter the number of nodes for the graph: " num_nodes

# Validate input
while ! validate_input "$num_nodes"; do
    echo "Please enter a valid integer."
    read -p "Enter the number of nodes for the graph: " num_nodes
done

# Prompt user for saturation level
read -p "Enter the saturation level for the graph (between 0 and 1): " saturation

# Validate input
while [[ $(bc <<< "$saturation < 0 || $saturation > 1") -eq 1 ]]; do
    echo "Saturation level must be between 0 and 1."
    read -p "Enter the saturation level for the graph (between 0 and 1): " saturation
done

# Output confirmation
echo "Graph parameters set:"
echo "Number of nodes: $num_nodes"
echo "Saturation level: $saturation"
