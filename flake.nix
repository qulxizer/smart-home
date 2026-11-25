{
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs =
    { nixpkgs, ... }:
    let
      system = "x86_64-linux"; # swap to aarch64-darwin if you're on Apple Silicon
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      devShells.${system}.default = pkgs.mkShell {
        packages = with pkgs; [
          clang-tools # gives you clangd, pre-wrapped so it actually finds Nix headers
          gcc
          gdb
          cmake
        ];

        shellHook = ''
          export CLANGD_QUERY_DRIVER=`which g++`
        '';
      };
    };
}
