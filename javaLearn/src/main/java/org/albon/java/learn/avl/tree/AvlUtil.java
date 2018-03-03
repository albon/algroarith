package org.albon.java.learn.avl.tree;

public class AvlUtil {
    public static int height(TreeNode left) {
        if (left == null) {
            return 0;
        }
        return left.getHeight();
    }
}
