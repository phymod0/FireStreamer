import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

class _ShelfItem extends StatefulWidget {
  final Movie movie;

  const _ShelfItem({required this.movie});

  @override
  State<_ShelfItem> createState() => _ShelfItemState();
}

class _ShelfItemState extends State<_ShelfItem> {
  @override
  Widget build(BuildContext context) {
    Movie movie = widget.movie;
    return Column(children: [
      Image.network(
        movie.coverImageURL,
        width: 100,
        height: 100,
        loadingBuilder: (context, child, loadingProgress) {
          if (loadingProgress == null) {
            return child;
          } else {
            return const CircularProgressIndicator();
          }
        },
      ),
      Text(movie.title),
    ]);
  }
}

class _Shelf extends StatefulWidget {
  final Future<List<Movie>> shelfContents;

  const _Shelf({required this.shelfContents});

  @override
  State<_Shelf> createState() => _ShelfState();
}

class _ShelfState extends State<_Shelf> {
  Widget createMovieShelf(List<Movie> movies) {
    return Row(
        children: movies.map((movie) => _ShelfItem(movie: movie)).toList());
    /*
    String display = "";
    for (Movie movie in movies) {
      if (display == "") {
        display = movie.title;
      } else {
        display = "$display\n    ${movie.title}";
      }
    }
    return Text("Got data:\n    $display");
    */
  }

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
              } else if (snapshot.hasData && snapshot.data != null) {
                return createMovieShelf(snapshot.data!);
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
  final String coverImageURL;

  Movie(jsonData)
      : title = jsonData["title"],
        coverImageURL = jsonData["cover_image_url"];
}

class NewMoviesShelf extends StatelessWidget {
  const NewMoviesShelf({super.key});

  @override
  Widget build(BuildContext context) {
    return _Shelf(shelfContents: createShelfContents());
  }

  Future<List<Movie>> createShelfContents() async {
    await Future.delayed(const Duration(seconds: 1));
    final response = await http.get(Uri.parse("http://10.0.0.234:3000/movies"));
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
