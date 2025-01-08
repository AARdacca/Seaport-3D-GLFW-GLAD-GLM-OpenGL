# Seaport 3D Project

This project is a 3D Seaport simulation created using **OpenGL**, **GLFW**, **GLAD**, and **GLM**. It was developed as part of the **CSE 426 Graphics Lab Project** under the **Department of Computer Science and Engineering** at the **University of Asia Pacific**.

## Project Details

- **Course Code**: CSE 426 Graphics Lab Project
- **University**: University of Asia Pacific
- **Contributors**:
  - Ali Ahasan ([GitHub](https://github.com/AARdacca)) [Email:
    aliahasan.dhaka@gmail.com]
  - Md Naimul Basher ([GitHub](https://github.com/naimulbasher)) [Email:
    naimulbasher122@gmail.com]
  - Adib Hossain ([GitHub](https://github.com/adib055)) [Email:
    adibhossain2001@gmail.com]

## Development Environment

- **IDE**: Visual Studio 2022
- **Technologies**: OpenGL, GLFW, GLAD, GLM

## Repository

[Seaport 3D Project GitHub Repository](https://github.com/AARdacca/Seaport-3D-GLFW-GLAD-GLM-OpenGL)

## Prerequisites

- Visual Studio 2022 installed
- C++ development tools

## Setup Instructions

### Step 1: Clone or Download the Repository

Clone the repository or download the ZIP file:
```bash
https://github.com/AARdacca/Seaport-3D-GLFW-GLAD-GLM-OpenGL
```

Extract the ZIP file if downloaded, and locate the `CG All in 1.zip`. Extract this ZIP file as well.

### Step 2: Open the Solution

After extraction, open the `Seaport3D.sln` file in Visual Studio 2022.

### Step 3: Setup Dependencies

#### Adding GLAD
1. Locate the `glad.c` file in the extracted files.
2. Add the file to your project:
   - Right-click on the project in **Solution Explorer**.
   - Choose **Add > Existing Item**.
   - Navigate to `glad.c` and add it to the project.

#### Include and Library Directory Configuration
1. Go to **Project > Properties**.
2. Navigate to **Configuration Properties > VC++ Directories**.
3. Set the following paths:
   - **Include Directories**: Add the path to the `include` folder.
   - **Library Directories**: Add the path to the `lib` folder.

#### Link Libraries
1. Go to **Configuration Properties > Linker > Input**.
2. Add the following dependencies in the **Additional Dependencies** field:
   - `glfw3.lib`
   - `opengl32.lib`

### Step 4: Build and Run
1. Build the solution using `Ctrl + Shift + B` or **Build > Build Solution**.
2. Run the project (▶️) to view the 3D Seaport simulation.

## Notes
- Ensure that the project is set to the correct **platform target** (x86 or x64) to match your GLFW and OpenGL library versions.
- If any issues occur during setup, verify that the include and library paths are correctly configured.

## License
This project follows the licensing terms stated in the repository.

---

Feel free to reach out to the contributors via their GitHub profiles for any questions or collaboration opportunities.
