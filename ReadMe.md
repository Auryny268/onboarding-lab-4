# Onboarding Lab 4  (NYU ProcDesign)
## Review
1. **Registry:** A collection of information about the packages that we wish to use in our project.

2. **Package:** The (third-party) source code files we want to integrate into our project.

3. **Interface Library:** differs from a "normal" library because it can consist of code/files that don't need to be compiled. Outside of System Verilog files, interface libraries are also useful if we want to create a library entirely out of header files (e.g. templated classes).

What’s the difference between an interface library and a “normal” library or executable? Can you think of any uses for this besides System Verilog files? (Think about source code used for generic programming)

4. **Top Modules:** System Verilog modules we'd like to be exposed for simulation (as opposed to modules that are used internally - perhaps as a component to one of our top modules).


## Additional Notes

**Package Manager:** The tool used integrate packages into our project (for ProcDesign we use `vcpkg`).

Required fields for a registry:
* `kind`: The type of registry (For ProcDesign this will always be `git`)
* `baseline`: The git hash to pull from (think object ID)
* `repository`: A link to the git repository
* `packages`: A list of packages that the registry will be responsible for

We keep track of the registries we're using in a given project with `vcpkg-configuration.json` file. Below is an example of a registry listing (file that tells `vcpkg` where to look for packages.):

```
{
  "default-registry": {
    "kind": "git",
    "baseline": "b4f29c54450ddfc7efd2989cb9d32158ae291b40",
    "repository": "https://github.com/microsoft/vcpkg.git"
  },
  "registries": []
}
```

- To get hash, go to registry repo page and click on `commits` and copy-paste hash
- `"nyu-*"` -> Tells `vcpkg` to provide every package beginning with "nyu-"

### Dependecies:
`vcpkg.json` is the file that describes our project, below is an example:

```
{
  "name": "week-four-lab",
  "version": "1.0.0",
  "description": "Template for week four lab",
  "homepage": "https://github.com/NYU-Processor-Design/onboarding-lab-4",
  "maintainers": [
    "Vito Gamberini <vito@gamberini.email>"
  ],
  "license": "CC0-1.0",
  "dependencies": []
}
```

The `dependencies` field is where we list the packages `vcpkg` will fetch for us.

### Libraries and Packages
`find_package()` takes three arguments:
* `nyu_cmake`: Name of package we want `cmake` to find
* `CONFIG`: Flag that changes the search behavior `cmakes` uses to find the package. (Not vital to understand)
* `REQUIRED`: Flag that tells `cmake` to throw a build error if requested package is not found

**NOTE:** The exact sematics of `cmake` conditional are not vital to understand for ProcDesign. If interested, one can read the [official docs](https://cmake.org/cmake/help/latest/command/if.html#basic-expressions).

**NOTE:** `enable_testing()` tells `cmake` we want it to generate files necessary to automatically run tests for us. 

When running `cmake`, we must set this conditional "on", which is accomplished by running the following command in the terminal:

```
cmake -DNYU_BUILD_TESTS=TRUE ..
```

(Assuming we're running `cmake` from inside the build directory.)

Info about Catch2's cmake integration is in the [official docs](https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md#automatic-test-registration)