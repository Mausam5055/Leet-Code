import java.util.*;

class MovieRentingSystem {

    // (shop, movie) -> price
    private Map<String, Integer> priceMap;

    // movie -> available shops (price, shop)
    private Map<Integer, TreeSet<int[]>> available;

    // rented movies (price, shop, movie)
    private TreeSet<int[]> rented;

    public MovieRentingSystem(int n, int[][] entries) {

        priceMap = new HashMap<>();
        available = new HashMap<>();

        rented = new TreeSet<>((a, b) -> {
            if (a[0] != b[0]) return a[0] - b[0];  // price
            if (a[1] != b[1]) return a[1] - b[1];  // shop
            return a[2] - b[2];                    // movie
        });

        for (int[] e : entries) {
            int shop = e[0], movie = e[1], price = e[2];

            priceMap.put(shop + "#" + movie, price);

            available
                .computeIfAbsent(movie, k -> new TreeSet<>(
                    (a, b) -> {
                        if (a[0] != b[0]) return a[0] - b[0]; // price
                        return a[1] - b[1];                  // shop
                    }))
                .add(new int[]{price, shop});
        }
    }

    // Search cheapest 5 shops for a movie
    public List<Integer> search(int movie) {

        List<Integer> res = new ArrayList<>();

        if (!available.containsKey(movie)) return res;

        TreeSet<int[]> set = available.get(movie);

        int count = 0;
        for (int[] p : set) {
            res.add(p[1]); // shop
            if (++count == 5) break;
        }

        return res;
    }

    // Rent movie from shop
    public void rent(int shop, int movie) {

        int price = priceMap.get(shop + "#" + movie);

        TreeSet<int[]> set = available.get(movie);

        set.remove(new int[]{price, shop});

        rented.add(new int[]{price, shop, movie});
    }

    // Drop (return)
    public void drop(int shop, int movie) {

        int price = priceMap.get(shop + "#" + movie);

        rented.remove(new int[]{price, shop, movie});

        available
            .computeIfAbsent(movie, k -> new TreeSet<>(
                (a, b) -> {
                    if (a[0] != b[0]) return a[0] - b[0];
                    return a[1] - b[1];
                }))
            .add(new int[]{price, shop});
    }

    // Report cheapest 5 rented movies
    public List<List<Integer>> report() {

        List<List<Integer>> res = new ArrayList<>();

        int count = 0;
        for (int[] r : rented) {
            res.add(Arrays.asList(r[1], r[2])); // shop, movie
            if (++count == 5) break;
        }

        return res;
    }
}
