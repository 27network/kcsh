{
  description = "dev-env for 42 projects";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-utils = {
      url = "github:numtide/flake-utils";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils
  }: flake-utils.lib.eachDefaultSystem
    (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        stdenv = pkgs.stdenvAdapters.useMoldLinker pkgs.clang17Stdenv;
      in
      {
        devShell = (pkgs.mkShell.override { inherit stdenv; }) {
          buildInputs = with pkgs; [
            readline
          ];
          nativeBuildInputs = with pkgs; [
            cloc
            valgrind
            gdb
          ];
        };
      }
    );
}
# vim: ts=2 sw=2 et

