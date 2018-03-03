package org.albon.java.learn.avl.tree;

public class TreeNode {

    private int data = 0;
    private int height = 1;
    private int freq = 1;
    private TreeNode left = null;
    private TreeNode right = null;

    public TreeNode() {
    }

    public TreeNode(int data) {
        this.data = data;
    }

    public TreeNode(int data, int height, int freq, TreeNode left, TreeNode right) {
        this.data = data;
        this.height = height;
        this.freq = freq;
        this.left = left;
        this.right = right;
    }

    public int getData() {
        return data;
    }

    public void setData(int data) {
        this.data = data;
    }

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    public int getFreq() {
        return freq;
    }

    public void setFreq(int freq) {
        this.freq = freq;
    }

    public TreeNode getLeft() {
        return left;
    }

    public void setLeft(TreeNode left) {
        this.left = left;
    }

    public TreeNode getRight() {
        return right;
    }

    public void setRight(TreeNode right) {
        this.right = right;
    }

    public void reComputeHeight() {
        setHeight(Math.max(AvlUtil.height(getLeft()), AvlUtil.height(getRight())) + 1);
    }

}
