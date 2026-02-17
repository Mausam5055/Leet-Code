import java.util.*;

class MovieRentingSystem {

    // (shop,movie) -> price
    private Map<String, Integer> priceMap = new HashMap<>();

    // movie -> available shops sorted by (price, shop)
    private Map<Integer, TreeSet<int[]>> available = new HashMap<>();

    // rented movies sorted by (price, shop, movie)
    private TreeSet<int[]> rented = new TreeSet<>(
        (a, b) -> {
            if (a[0] != b[0]) return a[0] - b[0];   // price
            if (a[1] != b[1]) return a[1] - b[1];   // shop
            return a[2] - b[2];                     // movie
        }
    );

    public MovieRentingSystem(int n, int[][] entries) {

        for (int[] e : entries) {
            int shop = e[0], movie = e[1], price = e[2];

            priceMap.put(shop + "#" + movie, price);

            available
                .computeIfAbsent(movie, k ->
                    new TreeSet<>((a, b) -> {
                        if (a[0] != b[0]) return a[0] - b[0];
                        return a[1] - b[1];
                    }))
                .add(new int[]{price, shop});
        }
    }

    // 🔎 Search cheapest shops for a movie
    public List<Integer> search(int movie) {

        List<Integer> res = new ArrayList<>();

        if (!available.containsKey(movie)) return res;

        int count = 0;
        for (int[] arr : available.get(movie)) {
            res.add(arr[1]); // shop
            if (++count == 5) break;
        }

        return res;
    }

    // 🛒 Rent movie
    public void rent(int shop, int movie) {

        int price = priceMap.get(shop + "#" + movie);

        available.get(movie).remove(new int[]{price, shop});

        rented.add(new int[]{price, shop, movie});
    }

    // 🔄 Drop movie
    public void drop(int shop, int movie) {

        int price = priceMap.get(shop + "#" + movie);

        rented.remove(new int[]{price, shop, movie});

        available.get(movie).add(new int[]{price, shop});
    }

    // 📊 Report cheapest rented movies
    public List<List<Integer>> report() {

        List<List<Integer>> res = new ArrayList<>();

        int count = 0;

        for (int[] arr : rented) {
            res.add(Arrays.asList(arr[1], arr[2]));
            if (++count == 5) break;
        }

        return res;
    }
}
