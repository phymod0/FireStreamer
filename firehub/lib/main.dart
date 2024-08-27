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

class PrimaryPage extends StatefulWidget {
  const PrimaryPage({super.key});

  @override
  _PrimaryPageState createState() => _PrimaryPageState();
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
        child: Column(
          children: <Widget>[
            Padding(
              padding: EdgeInsets.all(100),
              child: Align(
                alignment: Alignment.topLeft,
                child: Text(
                  'New movies',
                  style: Theme.of(context).textTheme.headlineLarge,
                ),
              ),
            )
          ],
        ),
      ),
    );
  }
}

class MoviesPage extends StatefulWidget {
  const MoviesPage({super.key});

  @override
  _MoviesPageState createState() => _MoviesPageState();
}

class _MoviesPageState extends State<MoviesPage> {
  void _navigateBackToHome(BuildContext context) {
    ScaffoldMessenger.of(context)
        .showSnackBar(SnackBar(content: Text('No movies available yet')));
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
              padding: EdgeInsets.all(100),
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
