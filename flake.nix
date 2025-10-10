{
  description = "A collection of personal solutions across several problem-solving platforms";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";

    systems.url = "github:nix-systems/default";
    flake-parts.url = "github:hercules-ci/flake-parts";
  };

  outputs =
    inputs@{
      flake-parts,
      systems,
      ...
    }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      systems = import systems;
      perSystem =
        { pkgs, ... }:
        {
          devShells.default = import ./shell.nix { inherit pkgs; };
          packages = import ./packages { inherit pkgs; };
        };
    };
}
