package org.albon.java.learn.avl.tree;

public class AvlTree {

    private TreeNode root = null;

    public void insertData(int data) {
        this.root = insertNode(this.root, data);
    }

    public void traverse() {
        System.out.println("traverse start: ");
        inOrderTraverse(root);
        System.out.println("traverse end: ");
    }

    public void deleteData(int data) {
        this.root = deleteNode(this.root, data);
    }

    private TreeNode deleteNode(TreeNode root, int data) {
        if (root == null) {
            return null;
        }

        if (root.getData() > data) {
            root.setLeft(deleteNode(root.getLeft(), data));
            if (2 == AvlUtil.height(root.getRight()) - AvlUtil.height(root.getLeft())) {
                if (root.getRight().getLeft() != null
                        && AvlUtil.height(root.getRight().getLeft()) > AvlUtil.height(root.getRight().getRight())) {
                    return doubleRotateRL(root);
                } else {
                    return singleRotateRight(root);
                }
            }
        } else if (root.getData() < data) {
            root.setRight(deleteNode(root.getRight(), data));
            if (2 == AvlUtil.height(root.getLeft()) - AvlUtil.height(root.getRight())) {
                if (root.getLeft().getRight() != null
                        && AvlUtil.height(root.getLeft().getRight()) > AvlUtil.height(root.getLeft().getLeft())) {
                    return doubleRotateLR(root);
                } else {
                    return singleRotateLeft(root);
                }
            }
        } else {
            if (root.getRight() != null && root.getLeft() != null) {
                // 找到右子数里最小的节点
                TreeNode right = root.getRight();
                while (right.getLeft() != null) {
                    right = right.getLeft();
                }

                root.setData(right.getData());
                root.setFreq(right.getFreq());

                root.setRight(deleteNode(root.getRight(), right.getData()));
                if (2 == AvlUtil.height(root.getLeft()) - AvlUtil.height(root.getRight())) {
                    if (root.getLeft().getRight() != null
                            && AvlUtil.height(root.getLeft().getRight()) > AvlUtil.height(root.getLeft().getLeft())) {
                        return doubleRotateLR(root);
                    } else {
                        return singleRotateLeft(root);
                    }
                }
            } else {
                if (root.getLeft() != null) {
                    root = root.getLeft();
                } else if (root.getRight() != null) {
                    root = root.getRight();
                } else {
                    root = null;
                }
            }
        }

        if (root != null) {
            root.reComputeHeight();
        }
        return root;
    }

    private void inOrderTraverse(TreeNode root) {
        if (root == null) {
            return;
        }

        inOrderTraverse(root.getLeft());
        System.out.println(root.getData());
        inOrderTraverse(root.getRight());
    }

    private TreeNode insertNode(TreeNode root, final int data) {
        if (root == null) {
            return new TreeNode(data);
        }

        if (root.getData() > data) {
            root.setLeft(insertNode(root.getLeft(), data));
            if (2 == AvlUtil.height(root.getLeft()) - AvlUtil.height(root.getRight())) {
                if (data < root.getLeft().getData()) {
                    return singleRotateLeft(root);
                } else {
                    return doubleRotateLR(root);
                }
            }
        } else if (root.getData() < data) {
            root.setRight(insertNode(root.getRight(), data));
            if (2 == AvlUtil.height(root.getRight()) - AvlUtil.height(root.getLeft())) {
                if (data > root.getRight().getData()) {
                    return singleRotateRight(root);
                } else {
                    return doubleRotateRL(root);
                }
            }
        } else {
            root.setFreq(root.getFreq() + 1);
        }

        root.reComputeHeight();
        return root;
    }

    // 右左情况下，先右旋，再左旋。这种旋转是，先让下面的节点旋转，再旋转上面的节点
    private TreeNode doubleRotateRL(TreeNode root) {
        root.setRight(singleRotateLeft(root.getRight()));
        return singleRotateRight(root);
    }

    // 右右情况下，向左旋转
    private TreeNode singleRotateRight(TreeNode root) {
        TreeNode newRoot = root.getRight();
        root.setRight(newRoot.getLeft());
        newRoot.setLeft(root);

        root.reComputeHeight();
        newRoot.reComputeHeight();
        return newRoot;
    }

    // 左右情况下，先左旋，后右旋。这种旋转是，先让下面的节点旋转，再旋转上面的节点
    private TreeNode doubleRotateLR(TreeNode root) {
        root.setLeft(singleRotateRight(root.getLeft()));
        return singleRotateLeft(root);
    }

    // 左左情况下，向右旋转
    private TreeNode singleRotateLeft(TreeNode root) {
        TreeNode newRoot = root.getLeft();
        root.setLeft(newRoot.getRight());
        newRoot.setRight(root);

        root.reComputeHeight();
        newRoot.reComputeHeight();
        return newRoot;
    }

    public static void main(String[] args) {
        AvlTree avlTree = new AvlTree();
        avlTree.insertData(5);
        avlTree.insertData(1);
        avlTree.insertData(3);
        avlTree.insertData(7);
        avlTree.insertData(9);

        avlTree.deleteData(5);

        avlTree.insertData(3);
        avlTree.insertData(11);
        avlTree.insertData(19);
        avlTree.insertData(12);
        avlTree.insertData(13);
        avlTree.insertData(14);
        avlTree.insertData(15);
        avlTree.insertData(15);
        avlTree.insertData(16);
        avlTree.insertData(17);
        avlTree.insertData(18);
        avlTree.insertData(19);
        avlTree.insertData(20);
        avlTree.insertData(21);
        avlTree.insertData(22);
        avlTree.insertData(23);
        avlTree.insertData(24);
        avlTree.insertData(25);

        avlTree.traverse();
    }
}
