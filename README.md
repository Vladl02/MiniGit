# MiniGit

MiniGit is a small C++17 command-line project that models a simplified version of Git for an Object-Oriented Programming homework assignment. It is not a real Git implementation. The goal is clean OOP design, readable architecture, templates, exceptions, and meaningful design patterns.

## Build

```bash
cmake -S . -B build
cmake --build build
```

On Windows with Visual Studio generators, the executable is usually created under `build/Debug/mgit.exe` or `build/Release/mgit.exe`.

## Commands

```bash
mgit init
mgit add <file>
mgit commit -m "message"
mgit status
mgit log
mgit cat-object <hash>
mgit checkout <commit_hash>
```

## Demo Scenario

```bash
mgit init
echo hello > hello.txt
mgit add hello.txt
mgit status
mgit commit -m "first commit"
mgit log
```

MiniGit stores repository data in:

```text
.minigit/
  objects/
  index
  HEAD
  refs/
    heads/
      main
```

## Object Model

The polymorphic base class is `GitObject`, with these derived classes:

- `Blob`: file content.
- `Tree`: staged file path to blob hash entries.
- `Commit`: tree hash, optional parent hash, author, timestamp, and message.

Each object supports `type()`, `serialize()`, and `clone()`.

## Design Patterns

- Command Pattern: `ICommand` is implemented by `InitCommand`, `AddCommand`, `CommitCommand`, `LogCommand`, `StatusCommand`, `CatObjectCommand`, and `CheckoutCommand`. `CommandParser` creates command objects from `argv`.
- Strategy Pattern: `ObjectDatabase` depends on `IHashStrategy`. `FnvHashStrategy` is used by default, and `SimpleHashStrategy` is also available.
- Builder Pattern: `CommitBuilder` constructs and validates `Commit` objects before they are stored.

## Templates

Class template:

- `ObjectStore<TObject>` provides typed storage over the object database.
- It is instantiated as `ObjectStore<Blob>`, `ObjectStore<Tree>`, and `ObjectStore<Commit>`.

Free function templates:

- `requireNotEmpty<T>` validates values with `.empty()`.
- It is used with `std::string` for commit messages and metadata, and with `std::vector<TreeEntry>` to reject empty commits.
- `printCollection<TCollection, TPrinter>` is used by `status` to print staged files.

## OOP Concepts Demonstrated

- Encapsulation: repository services such as `Index`, `RefManager`, `WorkingDirectory`, and `ObjectDatabase` hide their own persistence details.
- Inheritance and polymorphism: `GitObject` and `ICommand` are abstract interfaces with concrete implementations.
- Composition: `Repository` coordinates smaller focused classes instead of doing all work itself.
- Exceptions: invalid operations throw exceptions, such as missing repositories, missing files, corrupted index data, empty commit messages, and missing object hashes.
- Templates: `ObjectStore<TObject>`, `requireNotEmpty<T>`, and `printCollection<TCollection, TPrinter>`.
- SOLID principles: commands have single responsibilities, hashing is open for extension through strategies, and high-level storage code depends on abstractions.

## Notes

MiniGit intentionally does not implement real Git internals such as branches beyond `main`, merges, remotes, packfiles, diffs, or conflict resolution.
