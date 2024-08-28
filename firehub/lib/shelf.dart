import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

class _Shelf extends StatefulWidget {
  final Future<List<Movie>> shelfContents;

  const _Shelf({required this.shelfContents});

  @override
  State<_Shelf> createState() => _ShelfState();
}

class _ShelfState extends State<_Shelf> {
  @override
  Widget build(BuildContext context) {
    return SizedBox(
      height: 200,
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
                return Text("Error: ${snapshot.error}");
              } else if (snapshot.hasData) {
                String display = "";
                for (Movie movie in snapshot.data!) {
                  if (display == "") {
                    display = movie.title;
                  } else {
                    display = "$display\n    ${movie.title}";
                  }
                }
                return Text("Got data:\n    $display");
              } else {
                return const Text("NO DATA");
              }
            },
          ),
        ),
      ),
    );
  }
}

class Movie {
  final String title;

  Movie(jsonData) : title = jsonData["title"];
}

class NewMoviesShelf extends StatelessWidget {
  const NewMoviesShelf({super.key});

  @override
  Widget build(BuildContext context) {
    return _Shelf(shelfContents: createShelfContents());
  }

  Future<List<Movie>> createShelfContents() async {
    await Future.delayed(const Duration(seconds: 1));
    final response = await http.get(Uri.parse("http://localhost:3000/movies"));
    if (response.statusCode == 200) {
      final List<dynamic> jsonList = jsonDecode(response.body);
      final List<Movie> movies = [];
      for (var movieJson in jsonList) {
        movies.add(Movie(movieJson));
      }
      return movies;
    } else {
      throw Exception("Movie query failed");
    }
  }
}
