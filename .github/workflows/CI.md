<!-- TODO: move to wiki -->

```mermaid
flowchart
    CI([CI])
    Linux(Linux build)
    Windows(Windows build)
    BuildAfter[Build]
    Lint[Lint and format code]
    Doxygen[Generate documentation from Doxygen comments]
    IsMain{Is this the main branch?}
    IsDev{Is this the main or dev branch?}
    IsTag{Is the push made on a tag?}
    Release[Create a release]
    Mirror[Mirror the repository to the Epitech one]
    End([End, all is good 👌])

    CI --> Build
    CI --> Lint
    Build --> Linux
    Build --> Windows
    Linux --> BuildAfter
    Windows --> BuildAfter
    BuildAfter --> IsDev
    BuildAfter --> IsTag
    Lint --> IsDev
    Lint --> IsTag
    IsDev -->|Yes| Doxygen
    IsDev -->|No| End
    Doxygen --> IsMain
    IsMain -->|Yes| Mirror
    IsMain -->|No| End
    IsTag -->|Yes| Release
    Mirror --> End
```

To create a release, create a tag named following the [Semantic Versioning](https://semver.org) format.
