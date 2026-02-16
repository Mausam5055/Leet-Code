import java.util.*;

class Router {

    private int limit;
    private Queue<int[]> queue;
    private Set<String> seen;

    // destination -> timestamps (sorted)
    private Map<Integer, ArrayList<Integer>> destMap;

    public Router(int memoryLimit) {
        limit = memoryLimit;
        queue = new LinkedList<>();
        seen = new HashSet<>();
        destMap = new HashMap<>();
    }

    public boolean addPacket(int source, int destination, int timestamp) {

        String key = source + "#" + destination + "#" + timestamp;

        if (seen.contains(key)) return false;

        if (queue.size() == limit) removeOldest();

        int[] packet = new int[]{source, destination, timestamp};
        queue.offer(packet);
        seen.add(key);

        destMap
            .computeIfAbsent(destination, k -> new ArrayList<>())
            .add(timestamp);

        return true;
    }

    public int[] forwardPacket() {

        if (queue.isEmpty()) return new int[0];

        int[] packet = queue.poll();

        int source = packet[0];
        int destination = packet[1];
        int timestamp = packet[2];

        String key = source + "#" + destination + "#" + timestamp;
        seen.remove(key);

        ArrayList<Integer> list = destMap.get(destination);

        // Remove from front (oldest timestamp)
        list.remove(0);

        if (list.isEmpty()) destMap.remove(destination);

        return packet;
    }

    public int getCount(int destination, int startTime, int endTime) {

        if (!destMap.containsKey(destination)) return 0;

        ArrayList<Integer> list = destMap.get(destination);

        int left = lowerBound(list, startTime);
        int right = upperBound(list, endTime);

        return right - left;
    }

    private void removeOldest() {
        int[] packet = queue.poll();

        int source = packet[0];
        int destination = packet[1];
        int timestamp = packet[2];

        String key = source + "#" + destination + "#" + timestamp;
        seen.remove(key);

        ArrayList<Integer> list = destMap.get(destination);
        list.remove(0);

        if (list.isEmpty()) destMap.remove(destination);
    }

    // First index >= target
    private int lowerBound(ArrayList<Integer> list, int target) {
        int l = 0, r = list.size();
        while (l < r) {
            int m = (l + r) / 2;
            if (list.get(m) < target) l = m + 1;
            else r = m;
        }
        return l;
    }

    // First index > target
    private int upperBound(ArrayList<Integer> list, int target) {
        int l = 0, r = list.size();
        while (l < r) {
            int m = (l + r) / 2;
            if (list.get(m) <= target) l = m + 1;
            else r = m;
        }
        return l;
    }
}
