import java.util.*;

class Spreadsheet {

    private Map<String, Integer> map;

    public Spreadsheet(int rows) {
        map = new HashMap<>();
    }

    public void setCell(String cell, int value) {
        map.put(cell, value);
    }

    public void resetCell(String cell) {
        map.remove(cell);  // removing means value becomes 0
    }

    public int getValue(String formula) {
        // remove '='
        String expr = formula.substring(1);

        String[] parts = expr.split("\\+");

        return getVal(parts[0]) + getVal(parts[1]);
    }

    private int getVal(String s) {
        // if starts with letter → cell reference
        if (Character.isLetter(s.charAt(0))) {
            return map.getOrDefault(s, 0);
        }
        // otherwise number
        return Integer.parseInt(s);
    }
}
