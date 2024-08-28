import 'package:flutter/material.dart';

class _Shelf extends StatefulWidget {
  final Future<String> shelfContents;

  const _Shelf({required this.shelfContents});

  @override
  State<_Shelf> createState() => _ShelfState();
}

class _ShelfState extends State<_Shelf> {
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
    return _Shelf(shelfContents: createShelfContents());
  }

  Future<String> createShelfContents() async {
    await Future.delayed(const Duration(seconds: 1));
    return "New movies shelf";
  }
}
