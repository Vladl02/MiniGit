# MiniGit

MiniGit este o aplicație C++ simplificată care imită câteva comenzi de bază din Git.

## Comenzi

```text
mgit init
mgit add <fisier>
mgit commit -m "mesaj"
mgit status
mgit log
mgit cat-object <hash>
mgit checkout <commit_hash>
```

## Cerințe îndeplinite

- Clasă template: `ObjectStore<TObject>`.
- Instanțieri template: `ObjectStore<Blob>`, `ObjectStore<Tree>`, `ObjectStore<Commit>`.
- Atribut dependent de template: `std::map<std::string, TObject> objectCache`.
- Funcții template: `requireNotEmpty<T>` și `printCollection<TCollection, TPrinter>`.
- Design pattern Command: `ICommand` și clasele `AddCommand`, `CommitCommand`, `StatusCommand`, etc.
- Design pattern Builder: `CommitBuilder`.
- Design pattern Strategy: `IHashStrategy` și `SimpleHashStrategy`.

## Biblioteci folosite

Proiectul folosește doar biblioteca standard C++: `filesystem`, `fstream`, `memory`, `vector`, `map`, `string`, `optional`, `chrono`, `ctime`, `iomanip`, `sstream`.

## Stocare

Datele interne sunt salvate în folderul `.minigit`, unde se află obiectele, indexul și referința către ultimul commit.
