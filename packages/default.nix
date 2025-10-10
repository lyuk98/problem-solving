{
  pkgs ? import <nixpkgs> { },
  ...
}:
let
  lib = pkgs.lib;

  # Code paths
  path = {
    lee = rec {
      basedir = "Lee";
      boj = {
        dir = "${basedir}/Baekjoon Online Judge";
      };
    };
    jinju = rec {
      basedir = "Jinju";
      boj = {
        dir = "${basedir}/Baekjoon";
      };
    };
  };

  # List derivations based on provided coder, platform, and language
  solutions =
    {
      coder,
      platform,
      language,
    }:
    let
      # Directory containing solutions authored by provided coder and platform
      dir = ./.. + "/${path.${coder}.${platform}.dir}";

      # Entity to callPackage to depending on the language
      callee = {
        "c" = ./c.nix;
        "cpp" = ./cpp.nix;
        "java" = ./java.nix;
        "rs" = ./rust.nix;
      };
    in
    (builtins.listToAttrs (
      builtins.map
        # Create derivations from properties
        (properties: {
          name = properties.pname;
          value = pkgs.callPackage callee.${language} properties;
        })
        (
          # Read directory and apply a list of functions
          lib.pipe (builtins.readDir dir) [
            # Get directory names
            builtins.attrNames

            # Get problem numbers and filesets containing source files for specified language
            (
              directories:
              builtins.map (directory: {
                name = directory;
                problem = builtins.elemAt (lib.splitStringBy (
                  prev: curr: (builtins.match "[0-9]" prev) != null && (builtins.match "[0-9]" curr) == null
                ) false directory) 0;
                fs = lib.fileset.fileFilter (file: (file.hasExt language)) (dir + "/${directory}");
              }) directories
            )

            # Discard problems containing empty filesets
            (entries: builtins.filter (entry: ((builtins.length (lib.fileset.toList entry.fs)) > 0)) entries)

            # Create package properties
            (
              entries:
              builtins.map (
                {
                  name,
                  problem,
                  fs,
                }:
                {
                  pname = "${coder}-${platform}-${problem}-${language}";
                  problemDir = dir + "/${name}";
                  source = fs;
                }
              ) entries
            )
          ]
        )
    ));
in
# Lee/Baekjoon Online Judge (C)
(solutions {
  coder = "lee";
  platform = "boj";
  language = "c";
})
# Lee/Baekjoon Online Judge (C++)
// (solutions {
  coder = "lee";
  platform = "boj";
  language = "cpp";
})
# Lee/Baekjoon Online Judge (Rust)
// (solutions {
  coder = "lee";
  platform = "boj";
  language = "rs";
})
# Lee/Baekjoon Online Judge (Java)
// (solutions {
  coder = "lee";
  platform = "boj";
  language = "java";
})
# Jinju/Baekjoon (C++)
// (solutions {
  coder = "jinju";
  platform = "boj";
  language = "cpp";
})
# Jinju/Baekjoon (Java)
// (solutions {
  coder = "jinju";
  platform = "boj";
  language = "java";
})
