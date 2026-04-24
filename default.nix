{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  # 1. Build-time dependencies (compilers and tools)
  nativeBuildInputs = with pkgs; [
    cmake
    pkg-config
    gcc
  ];

  # 2. Runtime dependencies (the libraries themselves)
  buildInputs = with pkgs; [
    glfw
    libGL
    glm
  # Essential for windowing on Linux
    xorg.libX11
    xorg.libXcursor
    xorg.libXrandr
    xorg.libXinerama
    xorg.libXi
    wayland 
    libxkbcommon
  ];
    # Add spdlog or entt here if you decide to use them;

  # 3. Environment Variables (Critical for Linux/NixOS)
  shellHook = ''
    export LD_LIBRARY_PATH="${pkgs.libGL}/lib:${pkgs.glfw}/lib:$LD_LIBRARY_PATH"
    echo "Game Engine Environment Loaded!"
    echo "Libraries: GLFW, OpenGL (libGL), GLM"
  '';
}
