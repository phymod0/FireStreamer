import 'package:flutter/material.dart';
import 'constants.dart';

void main() {
  runApp(const FireHubApp());
}

class FireHubApp extends StatelessWidget {
  const FireHubApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'FireHub',
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(
          seedColor: const Color(0xFFBF9F00),
          brightness: Brightness.dark,
        ),
        useMaterial3: true,
      ),
      routes: <String, WidgetBuilder>{
        '/': (ctx) => const PrimaryPage(),
        '/movies': (ctx) => const MoviesPage(),
      },
    );
  }
}

class Shelf extends StatefulWidget {
  final Future<String> shelfContents;

  const Shelf({super.key, required this.shelfContents});

  @override
  State<Shelf> createState() => _ShelfState();
}

class _ShelfState extends State<Shelf> {
  @override
  Widget build(BuildContext context) {
    return SizedBox(
      height: 100,
      child: Align(
        alignment: Alignment.centerLeft,
        child: Padding(
          padding: const EdgeInsets.all(20),
          child: FutureBuilder(
            future: widget.shelfContents,
            builder: (ctx, snapshot) {
              if (snapshot.connectionState == ConnectionState.waiting) {
                return const CircularProgressIndicator();
              } else if (snapshot.hasError) {
                return const Text("Error!");
              } else {
                return Text("Got data: ${snapshot.data}");
              }
            },
          ),
        ),
      ),
    );
  }
}

class NewMoviesShelf extends StatelessWidget {
  const NewMoviesShelf({super.key});

  @override
  Widget build(BuildContext context) {
    return Shelf(shelfContents: createShelfContents());
  }

  Future<String> createShelfContents() async {
    await Future.delayed(const Duration(seconds: 1));
    return "New movies shelf";
  }
}

class PrimaryPage extends StatefulWidget {
  const PrimaryPage({super.key});

  @override
  State<PrimaryPage> createState() => _PrimaryPageState();
}

class _PrimaryPageState extends State<PrimaryPage> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Theme.of(context).colorScheme.inversePrimary,
        title: const PageTopBarTitle(title: PageTitles.primaryPageTitle),
        centerTitle: true,
      ),
      body: Center(
        child: Padding(
          padding: const EdgeInsets.all(100),
          child: Column(
            children: <Widget>[
              Align(
                alignment: Alignment.topLeft,
                child: Text(
                  'New movies',
                  style: Theme.of(context).textTheme.headlineLarge,
                ),
              ),
              const NewMoviesShelf(),
            ],
          ),
        ),
      ),
    );
  }
}

class MoviesPage extends StatefulWidget {
  const MoviesPage({super.key});

  @override
  State<MoviesPage> createState() => _MoviesPageState();
}

class _MoviesPageState extends State<MoviesPage> {
  void _navigateBackToHome(BuildContext context) {
    ScaffoldMessenger.of(context)
        .showSnackBar(const SnackBar(content: Text('No movies available yet')));
    Navigator.pushNamed(context, '/');
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Theme.of(context).colorScheme.inversePrimary,
        title: const PageTopBarTitle(title: PageTitles.moviesPageTitle),
        centerTitle: true,
      ),
      body: Center(
        child: Column(
          children: <Widget>[
            Padding(
              padding: const EdgeInsets.all(100),
              child: Align(
                alignment: Alignment.topLeft,
                child: Text(
                  'Search:',
                  style: Theme.of(context).textTheme.headlineLarge,
                ),
              ),
            )
          ],
        ),
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () => {_navigateBackToHome(context)},
        tooltip: 'Increment',
        child: const Icon(Icons.add),
      ),
    );
  }
}

class PageTopBarTitle extends StatelessWidget {
  const PageTopBarTitle({super.key, required this.title});

  final String title;

  @override
  Widget build(BuildContext context) {
    return Text(
      title,
      style: Theme.of(context).textTheme.titleMedium,
    );
  }
}
