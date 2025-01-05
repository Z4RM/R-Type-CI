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
    Lint --> IsDev
    IsDev -->|Yes| Doxygen
    IsDev -->|No| End
    Doxygen --> IsMain
    IsMain -->|Yes| Release
    IsMain -->|No| End
    Release --> Mirror
    Mirror --> End
```
